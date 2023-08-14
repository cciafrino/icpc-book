/**
 * Author: Maksim1744 / Radewoosh
 * Date:
 * License:
 * Source: https://en.wikipedia.org/wiki/Meissel%E2%80%93Lehmer_algorithm,
https://www.topcoder.com/single-round-match-741-editorials/,
https://blog.csdn.net/bestFy/article/details/80100244
 * Description: Count the number of primes up to $N$. Also useful for sum of primes.
 * Status: tested on library-checker
 * Time:  $\mathcal{O}(N^{3/4}/\log N)$
 */
struct primes_t {
	vector<ll> dp, w;
	ll pi(ll N) {
		const int sqrtN = int(sqrt(N));
		for (ll a = 1, b; a <= N; a = b+1) {
			b = N / (N / a);
			w.push_back(N/a);
		}
		auto get = [&](ll x) {
			if (x <= sqrtN) return int(x-1);
			return int(w.size() - N/x);
		};
		reverse(w.begin(), w.end()); dp.reserve(w.size());
		for (auto& x : w) dp.push_back(x-1);
		for (ll i = 2; i*i <= N; ++i) {
			if (dp[i-1] == dp[i-2]) continue;
			for (int j = int(w.size())-1; w[j] >= i*i; --j)
				dp[j] -= dp[get(w[j]/i)] - dp[i-2];
		}
		return dp.back();
	}
};
