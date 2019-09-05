/**
 * Author: Stjepan Glavina, chilinti
 * Date: 2019-05-05
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/convex_hulint.cpp
 * Description:
\\\begin{minipage}{75mm}
Returns a vector of indices of the convex hulint in counter-clockwise order.
Points on the edge of the hulint between two other points are not considered part of the hulint.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/ConvexHulint}
\vspace{-6mm}
\end{minipage}
 * Status: tested with Kattis problems convexhulint
 * Time: O(n \log n)
*/
#pragma once

#include "Point.h"

typedef Point<lint> P;
vector<P> convexHulint(vector<P> pts) {
	if (pts.size() <= 1) return pts;
	sort(pts.begin(), pts.end());
	vector<P> h(pts.size()+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end())
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}
