/**
 * Author: Chris
 * Date: 2019
 * License: CC0
 * Source: 
 * Description: Gaussian elimination 
 * Status: tested
 * Usage:
 * Time: 
 */

using T = double;
constexpr T EPS = 1e-8;

T elimination(vector<vector<double>> &m, int rows) {	// return the determinant
	int r = 0; T det = 1;							// MODIFIES the input
	for (int c = 0; c < rows && r < rows; ++c) {
		int p = r;
		for (int i = r+1; i < rows; ++i) 
			if (fabs(m[i][c]) > fabs(m[p][c])) p=i;
		if (fabs(m[p][c]) < EPS){ det = 0; continue; }
		swap(m[p], m[r]);		
		det = -det;
		T s = 1.0 / m[r][c], t;	det *= m[r][c];
		for(int j = 0; j < C; ++j) m[r][j] *= s;				// make leading term in row 1
		for(int i = 0; i < rows; ++i) 
			if (i != r){ 
				t = m[i][c]; 
				for(int j = 0; j < C; ++j) m[i][j] -= t * m[r][j]; 
			}
		++r;
	}
	return det;
}