/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: 
 * Status: 
 * Description: Pre-compute all the factorial numbers until $lim$.
 * Usage:
 * Time: $O(N + \log(mod))$
 */
num ncr(int n, int k) {
	num res = 1;
	for (int i = 1; i <= k; ++i) {
		res *= (n - i + 1);
		res /= i;
	}
	return res;
}
num ncr(int n, int k){
	if(k < 0 || k > n) return 0;
	return fact[n] * ifact[k] * ifact[n-k];
}