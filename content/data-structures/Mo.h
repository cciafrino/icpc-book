/**
 * Author: Chris
 * Date: 2019
 * License: CC0
 * Source: folklore
 * Description: Mo's algorithm example problem: Count how many elements appear at least two times in given range $[l, r]$.
 * Time: $(n + q)sqrt(n)$

 */


struct query_t {
	int l, r, id;
};

int n, q, total; // elements, queries, result.
const int sqn = sqrt(n);
vector<int> values(n), freq(n), result(m);
vector<query_t> queries(q);

sort(queries.begin(), queries.end(), [sqn](const query_t &a, const query_t &b) {
	if (a.l/sqn != b.l/sqn) return a.l < b.l;
	return a.r < b.r;
});

int lx = 0, r = -1;
for(query_t &q : queries) {
	auto add = [&](int i) {
		// Change if needed
		freq[values[i]]++;
		if (freq[values[i]] == 2) total += 2;
		else if (freq[values[i]] > 2) total++;
	}
	auto del = [&](int i) {
		// Change if needed
		freq[values[i]]--;
		if (freq[values[i]] == 1) total -= 2;
		else if (freq[values[i]] > 1) total--;
	}
	while(r < q.r) add(++r);
	while(l > q.l) add(--l);
	while(r > q.r) del(r--);
	while(l < q.l) del(l++);
	result[q.id] = total;
}



