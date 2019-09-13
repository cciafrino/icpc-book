/**
 * Author: Chris
 * License: CC0
 * Description: You are given $n$ types of items, you have $e[i]$ items of $i$-th type, and each item of $i$-th type weighs $w[i]$ and costs $c[i]$. What is the minimal cost you can get by picking some items weighing at most $W$ in total?
 * Status: tested
 * Source: https://petr-mitrichev.blogspot.com/2011/07/integral-bounded-knapsack-problem.html
 * Time: $O(Wn)$
 */

#include <MinQueue.h>

const int maxn = 1000;
const int maxm = 100000;
const int inf = 0x3f3f3f;

minQueue<int> q[maxm];

array<int, maxm> dyn; // the minimum cost dyn[i] I need to pay in order to fill the knapsack with total weight i
int w[maxn], e[maxn], c[maxn]; // weight, number, cost

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> w[i] >> c[i] >> e[i];
	for (int i = 1; i <= m; i++) dyn[i] = inf;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < w[i]; j++) q[j].clear();
		for (int j = 0; j <= m; j++) {
			minQueue<int> &mq = q[j % w[i]];
			if (mq.size() > e[i]) mq.pop();
			mq.add(c[i]);
			mq.push(dyn[j]);
			dyn[j] = mq.getMin();
		}
	}
	cout << "Minimum value i can pay putting a total weight " << m << " is " << dyn[m] << '\n'; 
	for (int i = 0; i <= m; i++) cout << dyn[i] << " " << i << '\n';
	cout << "\n";
}
