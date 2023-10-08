/**
 * Author: neal
 * License: CC0
 * Description:  Counts x, y >= 0 such that Ax + By <= C.
 * Status:
 * Time: 
 */

ll count_triangle(ll A, ll B, ll C) {
	if (C < 0) return 0;
	if (A > B) swap(A, B);
	ll p = C / B, k = B / A, d = (C - p * B) / A;
	return count_triangle(B - k * A, A, C - A * (k * p + d + 1)) + (p + 1) * (d + 1) + k * p * (p + 1) / 2;
}
