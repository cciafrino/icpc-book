/**
 * Author: Simon Lindholm
 * Date: 2016-09-06
 * Source: Wikipedia
 * Description: To count the number of spanning trees in an undirected graph $G$:
 * create an $N\times N$ matrix \texttt{mat}, and for each edge $(a, b) \in G$, do
 * \texttt{mat[a][a]++, mat[b][b]++, mat[a][b]--, mat[b][a]--}.
 * Remove the last row and column, and take the determinant.
 */
// Need to be tested, has some bug for sure
#include<ModTemplate.h>
constexpr int d = 3; // dimension of square matrix
num get(Matrix<num, d> &M) {
	Matrix<num, d> result;
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j) {
			num ed = M.d[i][j];
			result.d[i][i] = result.d[i][i] + ed;
			if (j != n-1) {
				result.d[j][j] = result.d[j][j] + ed;
				result.d[i][j] = result[i][j] - ed;
				result.d[j][i] = result[j][i] - ed;
			}
		}
		return det(result.d);
}