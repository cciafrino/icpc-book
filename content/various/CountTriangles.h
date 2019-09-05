/**
 * Author: neal
 * License: CC0
 * Description:  Counts x, y >= 0 such that Ax + By <= C.
 * Status:
 * Time: 
 */

lint count_triangle(lint A, lint B, lint C) {
	if (C < 0) return 0;
	if (A > B) swap(A, B);
	lint p = C / B;
	lint k = B / A;
	lint d = (C - p * B) / A;
	return count_triangle(B - k * A, A, C - A * (k * p + d + 1)) + (p + 1) * (d + 1) + k * p * (p + 1) / 2;
}
