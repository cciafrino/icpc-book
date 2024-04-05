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

pair<vector<int>, vector<int>> run_sieve2(int N) {
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

auto [primes, pfac] = run_sieve2(10000);

#include "../../content/number-theory/prime-factors.h"

template<typename T> vector<T> get_divisors(T N) {
	auto factors = prime_factorize(N);
	vector<T> ans; ans.reserve(int(sqrtl(N) + 1));
	auto dfs = [&](auto&& self, auto& ans, T val, int depth) -> void {
		auto& [P, E] = factors[depth];
		if (depth == int(factors.size())) ans.push_back(val);
		else {
			T X = 1;
			for (int pw = 0; pw <= E; ++pw, X *= P) {
				self(self, ans, val * X, depth + 1);
			}
		}
	}; dfs(dfs, ans, 1, 0);
	return ans;
}


int main() {
	const int lim = 10000;
	
	rep(m,2,lim) {
		vector<int> ans_log = get_divisors(m);
		vector<int> ans_sqrt = divisors(m);
		sort(ans_log.begin(), ans_log.end());
		sort(ans_sqrt.begin(), ans_sqrt.end());
		for (int u = 0; u < int(ans_log.size()); ++u) {
			assert(ans_log[u] == ans_sqrt[u]);
		}
	}

	cout<<"Tests passed!"<<endl;
}
