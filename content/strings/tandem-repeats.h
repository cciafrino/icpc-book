/**
 * Author: bqi343
 * License: 
 * Description: Find all $(i,p)$ such that s.substr($i,p$) == s.substr($i+p,p$). No two intervals with the same period intersect or touch.
 * Time: O(N \log N)
 * Status: tested on library-checker
 */
#pragma once
#include "suffix-array.h"
vector<array<int, 3>> run(int N, string S) {
	suffix_array_t A(S.begin(), S.end());
	reverse(S.begin(), S.end());
	suffix_array_t B(S.begin(), S.end());
	vector<array<int, 3>> ans;
	for (int p = 1; 2*p <= N; ++p)
		for (int i = 0, prv = -1; i+p <= N; i += p) {
			int l = i-B.get_lcp(N-i-p,N-i), r = i-p+A.get_lcp(i,i+p);
			if (l > r || l == prv) continue;
			ans.push_back({prv = l, r, p});
		}
	return ans;
}
