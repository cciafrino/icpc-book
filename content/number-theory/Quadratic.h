/**
 * Author: Chris
 * Source: 
 * Description: Solve $x^2\equiv n\mod p(0\le a<p)$ where $p$ is prime in $O(\log p)$. 
 * Status: Tested
 * Time:
 */

struct quadric {
	void multiply(lint &c, lint &d, lint a, lint b, lint w, lint p) { /// start-hash
		int cc = (a * c + b * d % p * w) % p;
		int dd = (a * d + b * c) % p; c = cc, d = dd; }
	bool solve(int n, int p, int &x) {
		if (n == 0) return x = 0, true; if (p == 2) return x = 1, true;
		if (mod_pow(n, p / 2, p) == p - 1) return false;
		lint c = 1, d = 0, b = 1, a, w;
		do { a = rand() % p; w = (a * a - n + p) % p;
			if (w == 0) return x = a, true;
		} while (mod_pow(w, p / 2, p) != p - 1);
		for (int times = (p + 1) / 2; times; times >>= 1) {
			if (times & 1) multiply (c, d, a, b, w, p);
			multiply (a, b, a, b, w, p); 
	    }
		return x = c, true; 
    } /// end-hash
};
