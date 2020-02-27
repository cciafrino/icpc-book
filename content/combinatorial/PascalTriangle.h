/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: 
 * Status: 
 * Description: Pre-compute all the Binomial Coefficients until $n$.
 * Usage:
 * Time: $O(N^2)$
 */

void init() {
	c[0][0] = 1;
	for (int i = 0; i < n; ++i) {
	    c[i][0] = c[i][i] = 1;
	    for (int j = 1; j < i; ++j)
	        c[i][j] = c[i-1][j-1] + c[i-1][j];
	}	
}

