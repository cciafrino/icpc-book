/**
 * Author: Chris
 * Date: 2019
 * License: CC0
 * Source: 
 * Description: Gauss-Jordan algorithm.
 * Status: tested
 * Usage:
 * Time: 
 */

bool elimination(vector<vector<double>> &m, int row, int col) {
	for (int i = 0; i < row; ++i) {
		int p = i; // Choose the biggest pivot
		for (int j = i; j < row; ++j) 
			if (abs(m[j][i]) > abs(m[p][i])) p = j;
		for (int j = i; j < col; ++j) swap(m[i][j], m[p][j]);
		if (!m[i][i]) return false;
		double c = 1.0/m[i][i]; // Normalize pivot line
		for(int j = 0; j < col; ++j) m[i][j] *= c;
		for(int k = i+1; k < col; ++k) {
			double c = -m[k][i]; // Remove pivot variable from other lines
			for(int j = 0; j < col; ++j) m[k][j] += c*m[i][j];
		}
	} // Make triangular system a diagonal one
	for(int i = row-1; i >= 0; --i) for(int j = i-1; j >= 0; --j) {
		double c = -m[j][i];
		for(int k = i; k < col; ++k) m[j][k] += c*m[i][k];
	}
	return true;
}