/**
 * Author: Chris
 * Source: 
 * Description: Find the smallest integer root of $x^2-ny^2=1$ when $n$ is not a square number, with the solution set $x_{k+1} = x_0x_k + ny_0y_k, y_{k+1} = x_0y_k + y_0x_k$.
 * Status: Tested
 * Time:
 */

pair<int,int> Pell(int n) {
	int p0 = 0, p1 = 1, q0 = 1, q1 = 0;
	int a0 = (int)sqrt(n), a1 = a0, a2 = a0;
	if(a0 * a0 == n) return {-1, -1};
	int g1 = 0, h1 = 1;
	while (1) {
		int g2 = -g1 + a1 * h1;
		int h2 = (n - g2 * g2)/h1;
		a2 = (g2 + a0)/h2;
		int p2 = a1 * p1 + p0;
		int q2 = a1 * q1 + q0;
		if (p2*p2 - n*q2*q2 == 1) return {p2, q2};
		a1 = a2; g1 = g2; h1 = h2; p0 = p1;
		p1 = p2; q0 = q1; q1 = q2;
	}
}
