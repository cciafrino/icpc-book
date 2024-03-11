/**
 * Author: LeticiaFCS
 * Source: radoslav11, https://codeforces.com/blog/entry/86731
 * Description: Lazy Li Chao Tree. Allows line add, segment add, segment update (only linear coeficient) and range query.
 * Status: Tested on atcoder 177F
 * Time: $O(\log N)$ except for segment add $O(\log^2 N)$
 */
template<typename T, T L, T R>
struct lichao_range{
	static const T inf = numeric_limits<T>::max() / 2;
	static bool first_best( T a, T b ){ return a < b; }
	static T get_best( T a, T b ){  return first_best(a, b) ? a : b;  }
	struct line{ 
		T m, b;
		T operator()( T x ){ return m*x + b; } 
		void apply(line other){
			m += other.m;
			b += other.b;
		}
	};
	struct node{ 
		line li, lazy;
		node *left, *right;
		T answer;
		node( line _li = {0, inf}): li(_li), lazy({0,0}), left(nullptr), right(nullptr), answer(inf){} 
		void apply(T l, T r, line other){
			li.apply(other);
			lazy.apply(other);
			answer = get_best(inf, answer + other.b);
		}
		~node(){
			delete left;
			delete right;
		}
	};
	node *root;
	lichao_range( line li = {0, inf} ): root ( new node(li) ) {}
	~lichao_range(){ delete root; }
	void updateAnswer(node *&cur, T l, T r){ 
		if(cur == nullptr) return;
		cur->answer = inf;
		if(cur->left != nullptr) cur->answer = get_best(cur->answer, cur->left->answer);
		if(cur->right != nullptr) cur->answer = get_best(cur->answer, cur->right->answer);
		cur->answer = get_best(cur->answer, cur->li(l));
		cur->answer = get_best(cur->answer, cur->li(r));
	}
	void propagateLazy(node *&cur, T l, T r){ 
		if(cur == nullptr) return;
		if(cur->left == nullptr) cur->left = new node;
		if(cur->right == nullptr) cur->right = new node;
		T mid = ( l + r ) >> 1;
		cur->left->apply( l, mid, cur-> lazy);
		cur->right->apply( mid+1, r, cur-> lazy);
		cur->lazy = {0, 0};
	}
	T query( node *cur , T l, T r, T lseg, T rseg){ 
		if(r < lseg || l > rseg) return inf;
		if(cur == nullptr) return inf;
		if(lseg <= l && r <= rseg) return cur->answer;
		T answer = get_best(cur->li(max(l, lseg)), cur->li(min(r, rseg)));
		if(l != r) propagateLazy(cur, l, r);
		T mid = ( l + r ) >> 1;
		answer = get_best(answer, query(cur->left, l, mid, lseg, rseg));
		answer = get_best(answer, query(cur->right, mid+1, r, lseg, rseg));
		updateAnswer(cur, l, r);
		return answer;
	}
	T query( T l, T r){ return query( root, L, R, l, r); }
	void add( line li, node *&cur, T l, T r){ 
		if(cur == nullptr){ 
			cur = new node(li);
			return;
		}
		T mid = ( l + r ) >> 1;
		propagateLazy(cur, l, r);
		if( first_best( li(mid), cur->li(mid) ) )
			swap(li, cur->li);
		if( first_best( li(l), cur->li(l) ) )
			add(li, cur->left, l, mid);   
		if( first_best( li(r), cur->li(r) ) )
			add(li, cur->right, mid + 1, r);
		updateAnswer(cur, l, r);
	}
	void add( T m, T b ){ add( {m, b}, root, L, R ); }
	void propagateLine(node *&cur, T l, T r){ 
		if(cur == nullptr) return;
		T mid = ( l + r ) >> 1;
		add(cur->li, cur->left, l, mid);
		add(cur->li, cur->right, mid+1, r);
		cur->li = {0, inf};
	}
	void addSegment( line li, node *&cur, T l, T r, T lseg, T rseg){ 
		if(r < lseg || l > rseg) return;
		if(cur == nullptr) cur =  new node;
		if(lseg <= l && r <= rseg){
			add(li, cur, l, r);
			return;
		}
		T mid = ( l + r ) >> 1;
		if(l != r){
			propagateLazy(cur, l, r);
			addSegment(li, cur->left, l, mid, lseg, rseg);
			addSegment(li, cur->right, mid+1, r, lseg, rseg);
		}
		updateAnswer(cur, l, r);
	}
	void addSegment( T m, T b, T left, T right){
		addSegment( {m, b}, root, L, R, left, right);
	}
	void updateSegment( T b, node *&cur, T l, T r, T lseg, T rseg){
		if(r < lseg || l > rseg) return;
		if(cur == nullptr) cur =  new node;
		if(lseg <= l && r <= rseg){
			cur->apply(l, r, {0, b});
			return;
		}
		T mid = ( l + r ) >> 1;
		propagateLazy(cur, l, r);
		propagateLine(cur, l, r);
		updateSegment(b, cur->left, l, mid, lseg, rseg);
		updateSegment(b, cur->right, mid+1, r, lseg, rseg);
		updateAnswer(cur, l, r);
	}
	void updateSegment( T b, T left, T right){
		updateSegment( b , root, L, R, left, right);
	}
};

