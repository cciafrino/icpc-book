/**
 * Author: Chris
 * Source: Chinese paper & CLRS
 * Description: Solves a general linear maximization problem: maximize $c^T x$ subject to $Ax \le b$, $x \ge 0$.
 * Status: Tested on codeforces 101492I
 * Time: O(NM * \#pivots), where a pivot may be e.g. an edge relaxation. O(2^n) in the general case.
 * WARNING-  segfaults on empty (size 0)
 * max cx st Ax<=b, x>=0
 * do 2 phases; 1st check feasibility;
 * 2nd check boundedness and ans
 */
using dbl = double; using vd = vector<dbl>;
vd simplex(vector<vd> A, vd b, vd c) { const dbl E = 1e-9;
	int n = A.size(), m = A[0].size() + 1, r = n, s = m-1;
	auto D = vector<vd>(n+2, vd(m+1));
	vector<int> ix = vector<int>(n + m);
	for (int i = 0; i < n + m; ++i) ix[i] = i;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m-1; ++j) D[i][j] = -A[i][j];
		D[i][m - 1] = 1; D[i][m] = b[i];
		if (D[r][m] > D[i][m]) r = i;
	}
	for (int j = 0; j < m-1; ++j) D[n][j] = c[j];
	D[n + 1][m - 1] = -1; int z = 0;
	for (dbl d;;) {
		if (r < n) { swap(ix[s], ix[r + m]);
			D[r][s] = 1.0/D[r][s];
			for (int j = 0; j <= m; ++j) if (j != s)
				D[r][j] *= -D[r][s];
			for (int i = 0; i <= n+1; ++i) if (i != r) {
				for (int j = 0; j <= m; ++j)
					if (j != s) D[i][j] += D[r][j] * D[i][s];
				D[i][s] *= D[r][s];
			}
		}
		r = -1; s = -1;
		for (int j = 0; j < m; ++j) if (s < 0 || ix[s] > ix[j]) 
			if (D[n+1][j]>E || D[n+1][j]>-E && D[n][j]>E) s = j;
		if (s < 0) break;
		for (int i = 0; i < n; ++i) if (D[i][s] < -E) {
			if (r<0 || (d = D[r][m]/D[r][s]-D[i][m]/D[i][s]) < -E
				|| d < E && ix[r+m] > ix[i+m]) r = i; 
		}
		if (r < 0) return vd(); // unbounded
	}
	if (D[n+1][m] < -E) return vd(); // infeasible
	vd x(m-1);
	for(int i=m; i < n+m; ++i) if(ix[i]<m-1) x[ix[i]]=D[i-m][m];
	dbl result = D[n][m]; return x; // ans: D[n][m]
}
