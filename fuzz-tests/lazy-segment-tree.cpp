#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/data-structures/LazySegmentTree.h"
// #include "../content/data-structures/old.h"

static unsigned R;
int ra() {
	R *= 791231;
	R += 1231;
	return (int)(R >> 1);
}
const int inf = 0x3f3f3f3f;
volatile int res;
int main() {
	int N = 10;
	vi v(N);
	iota(all(v), 0);
	random_shuffle(all(v), [](int x) { return ra() % x; });
	unique_ptr<segtree_t<int>> tr;
	tr.reset(new segtree_t<int>(N));
	for (int i = 0; i < N; ++i) {
		tr->update(i,i,v[i]);
	}
	rep(i,0,N) rep(j,0,N) if (i <= j) {
		int ma = 0;
		rep(k,i,j) ma = max(ma, v[k]);
		cout << ma <<  ' ' << tr->query(i,j) << endl;
		assert(ma == tr->query(i,j));
	}
	rep(it,0,1000000) {
		int i = ra() % (N+1), j = ra() % (N+1);
		if (i > j) swap(i, j);
		int x = (ra() % 10) - 5;

		int r = ra() % 100;
		if (r < 30) {
			::res = tr->query(i, j);
			int ma = 0;
			rep(k,i,j) {
				ma = max(ma, v[k]);
				cout << "V[i] = " << v[k] << endl;
			}
			cout << ma << ' ' << ::res << endl;
			assert(ma == ::res);
		}
		else if (r < 70) {
			tr->update(i, j, x);
			rep(k,i,j) v[k] += x;
		}
		else {
			tr->set(i, j, x);
			rep(k,i,j) v[k] = x;
		}
	}
	exit(0);
}
