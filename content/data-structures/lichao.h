/**
 * Author: LeticiaFCS
 * Source: radoslav11, https://codeforces.com/blog/entry/86731
 * Description: Line Segments Li Chao Tree. Allows line add, segment add and point query.
 * Status: Tested on yosupo
 * Time: $O(\log^2 N)$ for segment add, $O(\log N)$ for other operations
 */

template<typename T, T N>
struct lichao_t{
    static const T inf = numeric_limits<T>::max() / 2;
    bool first_best( T a, T b ){ return a < b; }
    T get_best( T a, T b ){  return first_best(a, b) ? a : b;  }
    struct line{ 
        T m, b;
        T operator()( T x ){ return m*x + b; } 
    };
    struct node{
        line li;
        node *left, *right;
        node( line _li = {0, inf}): li(_li), left(nullptr), right(nullptr){}
    };
    node *root;
    lichao_t( line li = {0, inf} ): root ( new node(li) ) {}
    T query( T x , node *cur , T l, T r){
        if(cur == nullptr) return inf;
        if(x < l || x > r) return inf;
        T mid = ( l + r ) / 2;   
        T ans =  cur->li(x);
        ans = get_best( ans , query(x, cur->left, l, mid) );
        ans = get_best( ans , query(x, cur->right, mid+1, r) );
        return ans;
    }
    T query( T x ){ return query( x, root, 0, N ); }
    void add( line li, node *&cur, T l, T r){
        if(cur == nullptr){ 
            cur = new node(li);
            return;
        }
        T mid = ( l + r ) / 2;
        if( first_best( li(mid), cur->li(mid) ) )
            swap(li, cur->li);
        if( first_best( li(l), cur->li(l) ) )
            add(li, cur->left, l, mid);   
        if( first_best( li(r), cur->li(r) ) )
            add(li, cur->right, mid + 1, r);
    }
    void add( T m, T b ){ add( {m, b}, root, 0, N ); }
    void addSegment( line li, node *&cur, T l, T r, T lseg, T rseg){
        if(r < lseg || l > rseg) return;
        if(cur == nullptr) cur =  new node;
        if(lseg <= l && r <= rseg){
            add(li, cur, l, r);
            return;
        }
        T mid = ( l + r ) / 2;
        if(l != r){
            addSegment(li, cur->left, l, mid, lseg, rseg);
            addSegment(li, cur->right, mid+1, r, lseg, rseg);
        }
    }
    void addSegment( T m, T b, T left, T right){
        addSegment( {m, b}, root, 0, N, left, right);
    }
};
