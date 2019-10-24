/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
#pragma once

struct UF {
	vector<int> e;
	UF(int n) : e(n, -1) {}
	bool same_set(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool unite(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return 0;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return 1;
	}
};
