/**
 * Author: Simon Lindholm
 * Date: 2016-12-08
 * Source: The regular matrix inverse code
 * Description: Invert matrix $A$ modulo a prime.
 * Returns rank; result is stored in $A$ unless singular (rank < n).
 * For prime powers, repeatedly set $A^{-1} = A^{-1} (2I - AA^{-1})\  (\text{mod }p^k)$ where $A^{-1}$ starts as
 * the inverse of A mod p, and k is doubled in each step.
 * Time: O(n^3)
 * Status: Slightly tested
 */
#include "../number-theory/ModPow.h"
int matInv(vector<vector<lint>>& A) {
	int n = A.size(); vi col(n);
	vector<vector<lint>> tmp(n, vector<lint>(n));
	for(int i = 0; i < n; ++i) tmp[i][i] = 1, col[i] = i;

	for(int i = 0; i < n; ++i) {///start-hash
		int r = i, c = i;
		for(int j = i; j < n; ++j) for(int k = i; k < n; ++k) if (A[j][k]) {
			r = j; c = k; goto found;
		}
		return i;
found:
		A[i].swap(A[r]); tmp[i].swap(tmp[r]);
		for(int j = 0; j < n; ++j) swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
		swap(col[i], col[c]);
		lint v = modpow(A[i][i], mod - 2);
		for(int i = i+1; i < n; ++i) {
			lint f = A[j][i] * v % mod;
			A[j][i] = 0;
			for(int k = i+1; k < n; ++k) A[j][k] = (A[j][k] - f*A[i][k]) % mod;
			for(int k = 0; k < n; ++k) tmp[j][k] = (tmp[j][k] - f*tmp[i][k]) % mod;
		}
		for(int j = i+1; j < n; ++j) A[i][j] = A[i][j] * v % mod;
		for(int j = 0; j < n; ++j) tmp[i][j] = tmp[i][j] * v % mod;
		A[i][i] = 1;
	}///end-hash

	for (int i = n-1; i > 0; --i) for(int j = 0; j < i; ++j) {///start-hash
		lint v = A[j][i];
		for(int k = 0; k < n; ++k) tmp[j][k] = (tmp[j][k] - v*tmp[i][k]) % mod;
	}

	for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j)
		A[col[i]][col[j]] = tmp[i][j] % mod + (tmp[i][j] < 0 ? mod : 0);
	return n;
}///end-hash
