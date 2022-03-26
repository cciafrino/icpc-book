/**
 * Author: ?
 * Date: 
 * License: CC0
 * Source: own work
 * Description: Solves $Ax = b$ over $\mathbb F_2$. If there are multiple solutions, one is returned arbitrarily.
 *  Returns true, or false if no solutions. Last column of $a$ is $b$. $c$ is the rank.
 * Time: O(n^2 m)
 * Status: Stress tested on 2018-2019 Brazil Subregional - M
 */
typedef bitset<1000> bs;

int solve_linear_z2(vector<bs>& A, vi& b, bs& x, int m) {
	int n = int(A.size()), rank = 0, br;
	assert(m <= sz(x));
	vector<int> col(m); iota(col.begin(), col.end(), 0);
	for(int i = 0; i < n; ++i) {
		for (br=i; br<n; ++br) if (A[br].any()) break;
		if (br == n) {
			for (int j = i; j < n; ++j) if(b[j]) return -1;
			break;
		}
		int bc = (int)A[br]._Find_next(i-1);
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		for (int j = 0; j < n; ++j) if (A[j][i] != A[j][bc]) {
			A[j].flip(i); A[j].flip(bc);
		}
		for (int j = i+1; j < n; ++j) if (A[j][i]) {
			b[j] ^= b[i];
			A[j] ^= A[i];
		}
		rank++;
	}

	x = bs();
	for (int i = rank; i--;) {
		if (!b[i]) continue;
		x[col[i]] = 1;
		for (int j = 0; j < i; ++j) b[j] ^= A[j][i];
	}
	return rank; // (multiple solutions if rank < m)
}
