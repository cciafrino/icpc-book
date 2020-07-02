/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: 
 * Status: 
 * Description: 
 * Usage:
 * Time: $O(min(k, n-k))$
 */
lint ncr(int n, int k) {
	lint res = 1, to = min(k, n-k);
	if (to < 0) return 0;
	for (int i = 0; i < to; ++i) {
		res = res * (n - i) / (i + 1);
	}
	return res;
}