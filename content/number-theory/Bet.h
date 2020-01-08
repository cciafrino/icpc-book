/**
 * Author: BenQ
 * Description: 
 * Given fractions $a \leq b$ with non-negative numerators and denominators, 
 * finds fraction $f$ with lowest denominator such that $a \leq f \leq b$. Should work with 
 * all numbers less than $2^{62}$.
 * Source: 
 * Status: tested
 */

lint cdiv(lint x, lint y) { return (x+y-1)/y; }
lint bet(lint P, lint A, lint L, lint R) { 
	if (A == 0) return L == 0 ? 0 : -1;
	lint c = cdiv(L,A); if (A*c <= R) return c;
	lint B = P % A; // P = k*A+B, L <= A(x-Ky)-By <= R 
	// => -R <= By % A <= -L
	auto y = bet(A,B, A-R % A, A-L%A); 
	return y == -1 ? y : cdiv(L+B*y, A) + P/A*y;
} 