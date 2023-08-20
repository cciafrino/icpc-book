/**
 * Author: BenQ
 * Date: 2023
 * License: 
 * Source: https://cp-algorithms.com/geometry/minkowski.html#distance-between-two-polygons
 * Description: Minkowski sum of two convex polygons given in ccw order.
 * Time: $O(N + M)$
 * Status: tested on gym - 104252G
 */
vector<P> minkowski_sum(vector<P> A, vector<P> B) {
	if (int(A.size()) > int(B.size())) swap(A, B);
	if (A.empty()) return {};
	if (int(A.size()) == 1) {
		for (auto& b : B) b = b + A.front();
		return B;
	}
	rotate(A.begin(), min_element(A.begin(), A.end()), A.end());
	rotate(B.begin(), min_element(B.begin(), B.end()), B.end());
	A.push_back(A[0]); A.push_back(A[1]);
	B.push_back(B[0]); B.push_back(B[1]);
	const int N = int(A.size()), M = int(B.size());
	vector<P> ans; ans.reserve(N+M);
	for (int i = 0, j = 0; i+2 < N || j+2 < M;) {
		ans.push_back(A[i] + B[j]);
		auto sgn = (A[i+1] - A[i]).cross(B[j+1] - B[j]);
		i += (sgn >= 0); j += (sgn <= 0);
	}
	return ans;
}
