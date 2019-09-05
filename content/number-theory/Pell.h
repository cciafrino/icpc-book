/**
 * Author: Chris
 * Source: 
 * Description: Find the smallest integer root of $x^2-ny^2=1$ when $n$ is not a square number, with the solution set $x_{k+1} = x_0x_k + ny_0y_k, y_{k+1} = x_0y_k + y_0x_k$.
 * Status: Tested
 * Time:
 */

template <int MAXN = 100000>
struct pell {
	pair <lint, lint> solve (lint n) { /// start-hash
		static lint p[MAXN], q[MAXN], g[MAXN], h[MAXN], a[MAXN];
		p[1] = q[0] = h[1] = 1; p[0] = q[1] = g[1] = 0;
		a[2] = (lint)(floor(sqrtl(n) + 1e-7L));
		for (int i = 2; ; ++i) {
			g[i] = -g[i - 1] + a[i] * h[i - 1];
			h[i] = (n - g[i] * g[i]) / h[i - 1];
			a[i + 1] = (g[i] + a[2]) / h[i];
			p[i] = a[i] * p[i - 1] + p[i - 2];
			q[i] = a[i] * q[i - 1] + q[i - 2];
			if (p[i] * p[i] - n * q[i] * q[i] == 1)
				return { p[i], q[i] }; 
        } 
    } /// end-hash
};
