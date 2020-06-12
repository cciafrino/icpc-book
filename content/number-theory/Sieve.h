/**
 * Author: Chris
 * Date: 
 * License:
 * Source: Yuhao Du and Chinese Paper.
 * Description: Prime sieve for generating all primes up to a certain limit. isprime$[i]$ is true iff $i$ is a primes.
 * Also useful if you need to compute any multiplicative function (in this case Moebius..).
 * Status: Works
 * Time: O(n)
 * Tested: stress-tested 
 */
vector<int> lp, primes, mu;
void run_sieve(int n) {
	lp.resize(n); primes.resize(n); mu.assign(n,-1);
	mu[1] = 1; int i, j, tot, x;
	for (i = 1; i <= n; ++i) lp[i] = i;
	for (i = 2, tot = 0; i <= n; ++i){
		if (lp[i] == i) primes[++tot] = i;
		for (j = 1; j <= tot && (x = primes[j]*i) <= n; ++j) {
			lp[x] = primes[j];
			mu[x] *= mu[i];
			if (i % primes[j] == 0) { mu[x] = 0; break; }
		} 
	}	
}
