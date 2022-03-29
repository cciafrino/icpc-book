/**
 * Author: LeticiaFCS
 * Source: radoslav11, https://codeforces.com/blog/entry/86731
 * Description: Lazy Li Chao Tree. Allows line add, segment add, segment update and point query.
 * Status: Stress tested
 * Time: $O(\log^2 N)$ for segment add, $O(\log N)$ for other operations
 */
template<typename T, T L, T R>
struct lichao_lazy{
    static const T inf = numeric_limits<T>::max() / 2;
    bool first_best( T a, T b ){ return a < b; }
    T get_best( T a, T b ){  return first_best(a, b) ? a : b;  }
    struct line{ // 88f949
        T m, b;
        T operator()( T x ){ return m*x + b; } 
        void apply(line other){
            m += other.m;
            b += other.b;
        }
    };
    struct node{ // e6c99b
        line li, lazy;
        node *left, *right;
        node( line _li = {0, inf}): li(_li), lazy({0,0}), left(nullptr), right(nullptr){} 
        void apply(line other){
            li.apply(other);
            lazy.apply(other);
        }
        ~node(){
        	delete left;
        	delete right;
        }
    };
    node *root;
    lichao_lazy( line li = {0, inf} ): root ( new node(li) ) {}
    ~lichao_lazy(){ delete root; }
    void propagateLazy(node *&cur){ // f09e7a
        if(cur == nullptr) return;
        if(cur->left == nullptr) cur->left = new node;
        if(cur->right == nullptr) cur->right = new node;
        cur->left->apply( cur-> lazy);
        cur->right->apply( cur-> lazy);
        cur->lazy = {0, 0};
    }
    T query( T x , node *cur , T l, T r){ // f56802
        if(x < l || x > r || l > r) return inf;
        if(cur == nullptr) return inf;
        T mid = ( l + r ) >> 1;
        if(l != r) propagateLazy(cur);
        T ans =  cur->li(x);
        ans = get_best( ans , query(x, cur->left, l, mid) );
        ans = get_best( ans , query(x, cur->right, mid+1, r) );
        return ans;
    }
    T query( T x ){ return query( x, root, L, R ); }
    void add( line li, node *&cur, T l, T r){ // 4191d1
        if(cur == nullptr){ 
            cur = new node(li);
            return;
        }
        T mid = ( l + r ) >> 1;
        propagateLazy(cur);
        if( first_best( li(mid), cur->li(mid) ) )
            swap(li, cur->li);
        if( first_best( li(l), cur->li(l) ) )
            add(li, cur->left, l, mid);   
        if( first_best( li(r), cur->li(r) ) )
            add(li, cur->right, mid + 1, r);
    }
    void add( T m, T b ){ add( {m, b}, root, L, R ); }
    void propagateLine(node *&cur, T l, T r){ // 8d3255
        if(cur == nullptr) return;
        T mid = ( l + r ) >> 1;
        add(cur->li, cur->left, l, mid);
        add(cur->li, cur->right, mid+1, r);
        cur->li = {0, inf};
    }
    void addSegment( line li, node *&cur, T l, T r, T lseg, T rseg){ // 1a6dd3
        if(r < lseg || l > rseg) return;
        if(cur == nullptr) cur =  new node;
        if(lseg <= l && r <= rseg){
            add(li, cur, l, r);
            return;
        }
        T mid = ( l + r ) >> 1;
        if(l != r){
            propagateLazy(cur);
            addSegment(li, cur->left, l, mid, lseg, rseg);
            addSegment(li, cur->right, mid+1, r, lseg, rseg);
        }
    }
    void addSegment( T m, T b, T left, T right){
        addSegment( {m, b}, root, L, R, left, right);
    }
    void updateSegment( line li, node *&cur, T l, T r, T lseg, T rseg){ // cce50c
        if(r < lseg || l > rseg) return;
        if(cur == nullptr) cur =  new node;
        if(lseg <= l && r <= rseg){
            cur->apply(li);
            return;
        }
        T mid = ( l + r ) >> 1;
        propagateLazy(cur);
        propagateLine(cur, l, r);
        updateSegment(li, cur->left, l, mid, lseg, rseg);
        updateSegment(li, cur->right, mid+1, r, lseg, rseg);
    }
    void updateSegment( T m, T b, T left, T right){
        updateSegment( {m, b}, root, L, R, left, right);
    }
};
