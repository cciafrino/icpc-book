/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m, and query maximum values at points x.
 *  Useful for dynamic programming.
 * Time: O(\log N)
 * Status: tested
 */
#pragma once

bool Q;
struct Line {
	mutable lint k, m, p;
	bool operator<(const Line& o) const {
		return Q ? p < o.p : k < o.k;
	}
};

struct LineContainer : multiset<Line> {/// start-hash
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const lint inf = lintONG_MAX;
	lint div(lint a, lint b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }/// end-hash
	bool isect(iterator x, iterator y) {/// start-hash
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}/// end-hash
	void add(lint k, lint m) {/// start-hash
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}/// end-hash
	lint query(lint x) {/// start-hash
		assert(!empty());
		Q = 1; auto l = *lower_bound({0,0,x}); Q = 0;
		return l.k * x + l.m;
	}/// end-hash
};
