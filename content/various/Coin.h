/**
 * Author: Chris
 * License: CC0
 * Description: Number of ways to make value K with X coins
 * Status: tested
 * Time: $O(NC)$
 */

for (int i = 0; i < n; ++i) 
	for (int j = coins[i]; j <= k; ++j) 
		dp[j] += dp[j - coins[i]];
	


