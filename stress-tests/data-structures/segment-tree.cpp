#include "../utilities/template.h"

static unsigned RA = 1231231;
int ra() {
	RA *= 574841;
	RA += 14;
	return RA >> 1;
}

#include "../../content/data-structures/segtree.h"

namespace nonabelian {

// https://en.wikipedia.org/wiki/Dihedral_group_of_order_6
const int lut[6][6] = {
	{0, 1, 2, 3, 4, 5},
	{1, 0, 4, 5, 2, 3},
	{2, 5, 0, 4, 3, 1},
	{3, 4, 5, 0, 1, 2},
	{4, 3, 1, 2, 5, 0},
	{5, 2, 3, 1, 0, 4}
};

}

struct nonabelian_node {
	int val;
	nonabelian_node() : val(0) {}
	nonabelian_node(int x) : val(x) {}
	void merge(const nonabelian_node& l, const nonabelian_node& r) {
		val = nonabelian::lut[l.val][r.val];
	}
	void update(int x) {
		val = x;
	}
};

struct seg_node { 
	int val;
	int mi, ma;
	seg_node() : mi(INT_MAX), ma(INT_MIN), val(0) {}
	seg_node(int x) : mi(x), ma(x), val(x) {}
	void merge(const seg_node& l, const seg_node& r) {
	    val = l.val + r.val;
	    mi = min(l.mi, r.mi);
	    ma = max(l.ma, r.ma);
	}
	void update(int x) {
	    mi = ma = val = x;
	}
};

int main() {

	if (0) {
		const int N = 10000;
		segtree<seg_node> tr(N);
		ll sum = 0;
		rep(it,0,1000000) {
			tr.update(ra() % N, ra());
			int i = ra() % N;
			int j = ra() % N;
			if (i > j) swap(i, j);
			auto v = tr.query(i, j+1).ma;
			sum += v;
		}
		cout << sum << endl;
		// return 0;
	}

	rep(n,1,10) {
		segtree<seg_node> tr(n);
		vi v(n, INT_MIN);
		rep(it,0,1000000) {
			int i = rand() % (n+1), j = rand() % (n+1);
			int x = rand() % (n+2);

			int r = rand() % 100;
			if (r < 30) {
				int ma = INT_MIN;
				rep(k,i,j) ma = max(ma, v[k]);
				assert(ma == tr.query(i,j).ma);
			}
			else {
				i = min(i, n-1);
				tr.update(i, x);
				v[i] = x;
			}
		}
	}

	rep(n,1,10) {
		segtree<nonabelian_node> tr(n);
		vi v(n);
		rep(it,0,1000000) {
			int i = rand() % (n+1), j = rand() % (n+1);
			int x = rand() % 6;

			int r = rand() % 100;
			if (r < 30) {
				int ma = 0;
				rep(k,i,j) ma = nonabelian::lut[ma][v[k]];
				assert(ma == tr.query(i,j).val);
			}
			else {
				i = min(i, n-1);
				tr.update(i, x);
				v[i] = x;
			}
		}
	}
	cout<<"Tests passed!"<<endl;
}
