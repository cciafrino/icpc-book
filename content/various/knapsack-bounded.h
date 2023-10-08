/**
 * Author: Chris
 * License:
 * Description: You are given $n$ types of items, each items has a weight and a quantity. 
 * Is possible to fill a knapsack with capacity k using any subset of items?
 * Status: tested
 * Source: https://petr-mitrichev.blogspot.com/2011/07/integral-bounded-knapsack-problem.html
 * Time: $O(Wn)$
 */
vector<int> how_many(n+1), dp(k+1);
dp[0] = 1;
for (int i = 1; i <= n; ++i) cin >> how_many[i];
for (int i = 1; i <= n; ++i) {
	for (int j = k-items[i]; j >= 0; --j) {
		if (dp[j]) {
			int x = 1;
			while (x <= how_many[i] && 
				j + x*items[i] <= k && !dp[j + x*items[i]]) {
				dp[j + x*items[i]] = 1; ++x;
			}
		}
	}
}
