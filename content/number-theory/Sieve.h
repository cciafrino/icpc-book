/**
 * Author: Chris
 * Date: 
 * License:
 * Source: Yuhao Du and Chinese Paper.
 * Description: Prime sieve for generating all primes up to a certain limit. $pfac[i]$ is the lowest prime factor of $i$.
 * Also useful if you need to compute any multiplicative function.
 * Status: stress-tested
 * Time: $O(N)$
 */
vector<int> run_sieve(int N) {
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
	return primes;
}
