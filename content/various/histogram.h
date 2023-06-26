/**
 * Author: Chris
 * Date: 2022
 * License: CC0
 * Source: 
 * Description:
 * Time: O(N)
 * Status: tested
 */
int max_area(const vector<int>& height) {
	const int N = int(height.size());
	vector<int> L(N), R(N);
	for (int i = N-1; i >= 0; --i) {
		R[i] = i+1;
		while (R[i] < N && height[i] <= height[R[i]]) R[i] = R[R[i]];
	}
	for (int i = 0; i < N; ++i) {
		L[i] = i-1;
		while (L[i] >= 0 && height[i] <= height[L[i]]) L[i] = L[L[i]];
	}
	int area = 0;
	for (int i = 0; i < N; ++i) {
		area = max(area, int64_t(R[i] - L[i] - 1) * heigh[i]);
	}
	return area;
}
