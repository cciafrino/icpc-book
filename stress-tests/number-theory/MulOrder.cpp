#include "../utilities/template.h"
#include "vector"

vector<int> divisors(int N) {
	vector<int> ans; ans.reserve(N);
	for (int d = 1; d*d <= N; ++d) {
		if (N % d == 0) {
			ans.push_back(d);
			if (N/d != d) ans.push_back(N/d);
		}
	}
	return ans;
}

template<typename T> T phi(T N){
	T s = N;
	for (int p = 2; p*p <= N; ++p) if (N % p == 0) {
		s = s / p * (p - 1);
		while (N % p == 0) N /= p;
	}
	if (N > 1) s = s / N * (N - 1);
	return s;
}

pair<vector<int>, vector<int>> run_sieve(int N) {
	vector<int> pfac(N + 1);
	vector<int> primes; primes.reserve(N+1);
	vector<int> mu(N + 1, -1); mu[1] = 1;
	vector<int> phi(N + 1); phi[1] = 1;
	for (int i = 2; i <= N; ++i) {
		if (!pfac[i]) { 
			pfac[i] = i; primes.push_back(i); 
			phi[i] = i - 1;
		}
		for (int p : primes) {
			if (p > N/i) break;
			pfac[p * i] = p;
			mu[p * i] *= mu[i];
			phi[p * i] = phi[i] * phi[p];
			if (i % p == 0) {
				mu[p * i] = 0;
				phi[p * i] = phi[i] * p;
				break;
			}
		}
	}
	return {primes, pfac};
}

auto [primes, pfac] = run_sieve(10000);
#include "../../content/number-theory/mul-order.h"

int main() {
	const int lim = 1000;
	
	rep(m,2,lim) {
		rep(a,1,lim) {
			if (__gcd(a, m) != 1) continue;

			int p = 1, pw = a % m, f = -1;
			for (; p <= lim; ++p) {
				if (pw % m == 1) {
					f = 1; 
					break;
				}
				pw = pw * a % m;
			}
			int border = -1;

			if (f >= 0) border = p;
			int morder = mul_order(a, m);
			assert(border == morder);
		}
	}

	cout<<"Tests passed!"<<endl;
}
