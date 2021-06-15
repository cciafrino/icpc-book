/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: BenQ
 * Description: Segment Tree with Lazy update. Can be extended to max/min/product/gcd, pay attention 
 * to propagate, f and update functions when extending. Be careful with each initialization aswell.
 * Status: Tested on USACO 2015 December Contest (Platinum) P3 - Counting Haybales.
 * Time: $O(\lg(N)*Q)$
 * Status: stress-tested
 */

template<class T, int N> struct segtree_t {
    static_assert(__builtin_popcount(N) == 1); // N must be power of 2
    const T unit = 0; T f(T a, T b) { return (a + b); }
    vector<T> seg, lazy; 
    segtree_t() : seg(2*N, unit), lazy(2*N) {}
    segtree_t(const vector<T>& other) : seg(2*N, unit), lazy(2*N) {
        for (int a = 0; a < int(other.size()); ++a) seg[a + N] = other[a];
        for (int a = N-1; a; --a) pull(a);
    }
    void push(int v, int L, int R) { 
	seg[v] += (R - L + 1) * lazy[v]; // dependent on operation
    	if (L != R) for(int i = 0; i < 2; ++i) lazy[2*v+i] += lazy[v]; /// prop to children
	lazy[v] = 0; 
    } // recalc values for current node
    void pull(int v) { seg[v] = f(seg[2*v], seg[2*v+1]); }
    void build() { for(int i = N-1; i > 0; --i) pull(i); }
    void upd(int mi,int ma,T delta,int v = 1,int L = 0, int R = N-1) {
    	push(v,L,R); if (ma < L || R < mi) return;
    	if (mi <= L && R <= ma) { 
	    lazy[v] = delta; push(v,L,R); return; }
	int M = (L+R)/2; upd(mi,ma,delta,2*v,L,M); 
    	upd(mi,ma,delta,2*v+1,M+1,R); pull(v);
    }
    T query(int mi, int ma, int v = 1, int L = 0, int R = N-1) {
    	push(v,L,R); if (mi > R || L > ma) return unit;
	if (mi <= L && R <= ma) return seg[v];
    	int M = (L+R)/2; 
	return f(query(mi,ma,2*v,L,M),query(mi,ma,2*v+1,M+1,R));
    }
};
