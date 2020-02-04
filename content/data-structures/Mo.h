/**
 * Author: Chris
 * Date: 2019
 * License: CC0
 * Source: folklore
 * Description: Mo's algorithm example problem: Count how many elements appear at least two times in given range $[l, r]$.
 * For path queries on trees, flatten the tree by DFSing and pushing even-depth nodes at entry and odd-depth nodes at exit.
 * If you need to squeeze Mo's in the TL and Q is greater than N, consider Hilbert Curves. Will work much faster.
 * Time: $(n + q)sqrt(n)$
 * Status: Tested on SPOJ DQUERY
 */

struct query_t { int l, r, id; };
int n, m, total = 0; // elements, queries, result.
const int sqn = sqrt(n), maxv = 1000000;
vector<int> values(n), freq(2*maxv), result(m);
vector<query_t> queries(m);

sort(queries.begin(), queries.end(), [sqn](const query_t &a, const query_t &b) {
	if (a.l/sqn != b.l/sqn) return a.l < b.l;
	return a.r < b.r;
});

/*
Mo's using Hilbert Curves.

constexpr int lgn = 20, maxn = 1 << lgn;
struct query_t {
	int l, r, id;
	inline lint order() const {
		int x = l, y = r;
		lint d = 0;
		for (int s = 1 << (lgn - 1); s; s >>= 1) {
			bool rx = x & s, ry = y & s;
			d = d << 2 | rx * 3 ^ static_cast<int>(ry);
			if (!ry) {
				if (rx) {
					x = maxn - x;
					y = maxn - y;
				}
				swap(x, y);
			}
		}
		return d;
	}	
};
sort(queries.begin(), queries.end(), [&](const query_t &a, const query_t &b) {
	return a.order() < b.order();	
});
*/

int l = 0, r = -1;
for(query_t &q : queries) {
	auto add = [&](int i) {
		// Change if needed
		++freq[values[i]];
		if (freq[values[i]] == 2) total += 2;
		else if (freq[values[i]] > 2) ++total;
	};
	auto del = [&](int i) {
		// Change if needed
		--freq[values[i]];
		if (freq[values[i]] == 1) total -= 2;
		else if (freq[values[i]] > 1) --total;
	};
	while(r < q.r) add(++r);
	while(l > q.l) add(--l);
	while(r > q.r) del(r--);
	while(l < q.l) del(l++);
	result[q.id] = total;
}



