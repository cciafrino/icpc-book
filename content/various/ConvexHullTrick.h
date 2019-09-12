/**
 * Author: Arthur Pratti Dadalto
 * License: CC0
 * Source: Codeforces
 * Description: Transforms dp of the form (or similar) $dp[i] = min_{j < i}(dp[j] + b[j] * a[i]$).
		Time goes from $O(n^2)$ to $O(n \log n)$, if using online line container, or $O(n)$ if
		lines are inserted in order of slope and queried in order of $x$.
		To apply try to find a way to write the factor inside minimization as a linear function
		of a value related to i. Everything else related to j will become constant.
 * Status: tested on https://codeforces.com/contest/319/problem/C
 */
#include<LineContainer.h>

array<lint, 112345> dyn, a, b;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    dyn[0] = 0;
    LineContainer cht;
    cht.add(-b[0], 0);
    for (int i = 1; i < n; ++i) {
        dyn[i] = cht.query(a[i]);
        cht.add(-b[i], dyn[i]);
    }
    // Original DP O(n^2).
	// for (int i = 1; i < n; i++) {
	// 	dyn[i] = INF;
	// 	for (int j = 0; j < i; j++)
	// 		dyn[i] = min(dyn[i], dyn[j] + a[i] * b[j]);
	// }
	cout << -dyn[n-1] << '\n';
}
