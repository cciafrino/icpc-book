/**
 * Author: Chris
 * License:
 * Description: You are given $n$ types of items, each items has a weight and a quantity. 
 * Is possible to fill a knapsack with capacity X using any subset of items?
 * Status: tested
 * Source: https://petr-mitrichev.blogspot.com/2011/07/integral-bounded-knapsack-problem.html
 * Time: $O(W \cdot N)$
 */
auto solve(vi weight, vi cnt, int X) {
	vector<int> dp(X+1, 0);
	for (int i = 0; i < N; ++i)
		for (int j = X-weight[i]; j >= 0; --j) {
			if (!dp[j]) continue;
			int k = cnt[i], s = j + weight[i];
			while (k > 0 && s <= X && !dp[s])
				dp[s] = 1, --k, s += weight[i];
		}
	return dp[X];
}
