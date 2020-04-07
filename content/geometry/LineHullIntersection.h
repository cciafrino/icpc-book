/**
 * Author: Oleksandr Bacherikov, chilli
 * Date: 2019-05-07
 * License: Boost Software License
 * Source: https://github.com/AlCash07/ACTL/blob/master/include/actl/geometry/algorithm/intersect/line_convex_polygon.hpp
 * Description: Line-convex polygon intersection. The polygon must be ccw and have no colinear points.
 * lineHull(line, poly) returns a pair describing the intersection of a line with the polygon:
 *  \begin{itemize*}
 *    \item $(-1, -1)$ if no collision,
 *    \item $(i, -1)$ if touching the corner $i$,
 *    \item $(i, i)$ if along side $(i, i+1)$,
 *    \item $(i, j)$ if crossing sides $(i, i+1)$ and $(j, j+1)$.
 *  \end{itemize*}
 *  In the last case, if a corner $i$ is crossed, this is treated as happening on side $(i, i+1)$.
 *  The points are returned in the same order as the line hits the polygon.
 * \texttt{extrVertex} returns the point of a hull with the max projection onto a line.
 * Status: fuzz-tested
 * Time: O(N + Q \log n)
 */
#include "Point.h"

typedef array<P, 2> Line;
#define cmp(i,j) sgn(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
int extrVertex(vector<P>& poly, P dir) { ///start-hash
	int n = poly.size(), left = 0, right = n;
	if (extr(0)) return 0;
	while (left + 1 < right) {
		int m = (left + right) / 2;
		if (extr(m)) return m;
		int ls = cmp(left + 1, left), ms = cmp(m + 1, m);
		(ls < ms || (ls == ms && ls == cmp(left, m)) ? right : left) = m;
	}
	return left;
}///end-hash

#define cmpL(i) sgn(line[0].cross(poly[i], line[1]))
array<int, 2> lineHull(Line line, vector<P> poly) { ///start-hash
	int endA = extrVertex(poly, (line[0] - line[1]).perp());
	int endB = extrVertex(poly, (line[1] - line[0]).perp());
	if (cmpL(endA) < 0 || cmpL(endB) > 0)
		return {-1, -1};
	array<int, 2> res;
	for(int i = 0; i < 2; ++i) {
		int left = endB, right = endA, n = poly.size();
		while ((left + 1) % n != right) {
			int m = ((left + right + (left < right ? 0 : n)) / 2) % n;
			(cmpL(m) == cmpL(endB) ? left : right) = m;
		}
		res[i] = (left + !cmpL(right)) % n;
		swap(endA, endB);
	}
	if (res[0] == res[1]) return {res[0], -1};
	if (!cmpL(res[0]) && !cmpL(res[1]))
		switch ((res[0] - res[1] + sz(poly) + 1) % poly.size()) {
			case 0: return {res[0], res[0]};
			case 2: return {res[1], res[1]};
		}
	return res;
} ///end-hash
