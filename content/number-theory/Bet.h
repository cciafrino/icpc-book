/**
 * Author: Chris
 * Description: Find first $x$ such that $L \leq Ax$ (mod p) $\leq R$.
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