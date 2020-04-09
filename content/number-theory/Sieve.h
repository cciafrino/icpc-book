/**
 * Author: Chris
 * Date: 
 * License:
 * Source: Yuhao Du and Chinese Paper.
 * Description: Prime sieve for generating all primes up to a certain limit. isprime$[i]$ is true iff $i$ is a primes.
 * Also useful if you need to compute any multiplicative function (in this case Moebius..).
 * Status: Works
 * Time: 
 */
vector<int> lp, primes, mu;
void run_sieve(int n) {
	lp.resize(n); primes.resize(n); mu.resize(n);
	mu[1] = 1;
	int i, j, tot, t1;
	for (i = 1; i <= n; ++i) lp[i] = i;
	for (i = 2, tot = 0; i <= n; ++i){
		if (lp[i] == i) primes[++tot] = i;
		for (j = 1; j <= tot && (t1 = primes[j] * i) <= n; ++j) {
			lp[t1] = primes[j];
			mu[t1] *= mu[i];
			if (i % primes[j] == 0) break;
		} 
	}	
}
