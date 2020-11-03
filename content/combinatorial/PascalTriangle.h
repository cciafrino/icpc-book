/**
 * Author: Chris
 * Date: 2020
 * License: CC0
 * Source: 
 * Status: 
 * Description: Pre-compute all the Binomial Coefficients until $n$.
 * Usage:
 * Time: $O(N^2)$
 */
ll C[1010][1010];
for (int n = 0; n <= 1000; ++n) {
	C[n][0] = C[n][n] = 1;
	for (int k = 1; k < n; ++k) {
		C[n][k] = (C[n - 1][k - 1] + C[n - 1][k]) % mod;
	}
}
