/**
 * Author: Chris
 * Description: Lagrange Polynomials. 
 * Source: https://codeforces.com/contest/622/problem/F
 * Time: $O(N)$
 */
#include "ModPow.h"
#include "ModInv.h"
#include "Factorial.h"

template<typename T>
struct Lagrange {
	const int n;
	vector<T> f, den;
	Lagrange(vector<T> other) : f(other), n(other.size()) {
		den.resize(n);
		for(int i = 0; i < n; ++i) {
			f[i] = (f[i] % mod + mod) % mod;
			den[i] = ifact[n-i-1] * ifact[i] % mod;
			if((n-i-1) % 2 == 1) 
				den[i] = (mod - den[i]) % mod;
		}
	}
	T interpolate(T x) {
		x %= mod;
		vector<T> l, r;
		l.resize(n); r.resize(n);
		l[0] = r[n-1] = 1;
		for (int i = 1; i < n; ++i) 
			l[i] = l[i-1] * (x - (i-1) + mod) % mod;
		for (int i = n-2; i >= 0; --i) 
			r[i] = r[i+1] * (x - (i+1) + mod) % mod;
		T ans = 0;
		for (int i = 0; i < n; ++i) {
			T coef = l[i] * r[i] % mod;
			ans = (ans + coef * f[i] % mod * den[i]) % mod;
		}
		return ans;
	}
};