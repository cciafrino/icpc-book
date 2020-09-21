#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int inf = 1e9;
template<class T, int N> struct segtree_t {
    static_assert(__builtin_popcount(N) == 1); // SZ must be power of 2
    const T unit = -inf; T f(T a, T b) { return max(a, b); }
    vector<T> seg, lazy; 
    segtree_t() : seg(2*N, unit), lazy(2*N, unit) {}
    segtree_t(const vector<T>& other) : seg(2*N, unit), lazy(2*N) {
        for (int a = 0; a < int(other.size()); ++a) seg[a + N] = other[a];
        for (int a = N-1; a; --a) pull(a);
    }
    void push(int v, int L, int R) { 
	seg[v] += lazy[v]; // dependent on operation
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

static unsigned R;
int ra() {
	R *= 791231;
	R += 1231;
	return (int)(R >> 1);
}

volatile int res;
int main() {
	int N = 10;
	vi v(N);
	iota(all(v), 0);
	random_shuffle(all(v), [](int x) { return ra() % x; });
	segtree_t<int, 1 << 18> seg(v);
	rep(i,0,N) rep(j,0,N) if (i <= j) {
		int ma = -inf;
		rep(k,i,j) ma = max(ma, v[k]);
		cerr << ma << ' ' << seg.query(i, j-1) << endl;
		assert(ma == seg.query(i,j-1));
	}
	rep(it,0,1000000) {
		int i = ra() % (N+1), j = ra() % (N+1);
		if (i > j) swap(i, j);
		int x = (ra() % 10) - 5;

		int r = ra() % 100;
		if (r < 30) {
			::res = seg.query(i, j-1);
			int ma = -inf;
			rep(k,i,j) ma = max(ma, v[k]);
			assert(ma == ::res);
		}
		else if (r < 70) {
			seg.upd(i, j-1, x);
			rep(k,i,j) v[k] += x;
		}
		else {
			//tr->set(i, j, x);
			//rep(k,i,j) v[k] = x;
		}
	}
	cout<<"Tests passed!"<<endl;
}
