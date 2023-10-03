/**
 * Author: Chris
 * Description: Generate all factors of $n$ given it's prime factorization.
 * Time: $O(\frac{\sqrt N}{\log N})$
 * Status: stress tested
 */
#include "prime-factors.h"
template<typename T> vector<T> get_divisors(T N) {
	auto factors = prime_factorize(N);
	vector<T> ans; ans.reserve(int(sqrtl(N) + 1));
	auto dfs = [&](auto&& self, auto& ans, T val, int d) -> void{
		auto& [P, E] = factors[d];
		if (d == int(factors.size())) ans.push_back(val);
		else {
			T X = 1;
			for (int pw = 0; pw <= E; ++pw, X *= P)
				self(self, ans, val * X, d + 1);
		}
	}; dfs(dfs, ans, 1, 0);
	return ans;
}
