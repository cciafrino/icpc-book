/**
 * Author: Chris
 * Date: 
 * License:
 * Source: Yuhao Du and Chinese Paper.
 * Description: Prime sieve for generating all primes up to a certain limit. $lp[i]$ is the lowest prime factor of $i$.
 * Also useful if you need to compute any multiplicative function (in this case Moebius..).
 * Status: stress-tested
 * Time: $O(n)$
 */
vector<int> lp, primes, mu;
void run_sieve(int n) {
	lp.resize(n+1); mu.assign(n+1,-1);
	mu[1] = 1; int p;
	iota(lp.begin(), lp.end(), 0);
	for (int i = 2, tot = 0; i <= n; ++i){
		if (lp[i] == i)  primes.push_back(i);
		for (int j = 0; j < primes.size() && (p = primes[j]*i) <= n; ++j) {
			lp[p] = primes[j];
			mu[p] *= mu[i];
			if (i % primes[j] == 0) { mu[p] = 0; break; }
		} 
	}	
}