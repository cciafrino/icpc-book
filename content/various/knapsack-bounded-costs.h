/**
 * Author: Chris
 * License: CC0
 * Description: You are given $N$ types of items, you have $cnt[i]$ items of $i$-th type, and each item of $i$-th type $weight[i]$ and $cost[i]$. What is the maximal cost you can get by picking some items weighing exactly $X$ in total?
 * Status: tested
 * Source: https://petr-mitrichev.blogspot.com/2011/07/integral-bounded-knapsack-problem.html
 * Time: $O(N \cdot W)$
 */
#include"../data-structures/monotonic-queue.h"
auto solve(vi weight, vi cost, vi cnt, int X) {
	vector<int> dp(X+1, 0); int N = int(weight.size());
	vector<max_monotonic_queue<int>> M(X+1);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < min(X+1, weight[i]); ++j) M[j] = max_monotonic_queue<int>();
		for (int j = 0; j <= X; ++j) {
			auto& que = M[j % weight[i]];
			if (cur_que.size() > cnt[i]) que.pop();
			que.add(cost[i]);
			que.push(dp[j]);
			dp[j] = que.get_val();
		}
	} return dp[X];
}
