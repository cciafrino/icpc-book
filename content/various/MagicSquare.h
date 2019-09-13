/**
 * Author: Chris
 * Date: 2016-08-23
 * License: CC0
 * Source: me
 * Description: 
 */
 
 int mat[MAXN][MAXN], n;	//0-indexed

void magicsquare() {
	int i=n-1, j=n/2;
	memset(&mat, 0, sizeof mat);
	for(int k = 1; k <= n*n; k++) {
		mat[i][j] = k;
		if (mat[(i+1)%n][(j+1)%n] > 0) {
			i = (i-1+n)%n;
		}
		else {
			i = (i+1)%n;
			j = (j+1)%n;
		}
	}
}

