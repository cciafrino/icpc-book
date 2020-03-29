/**
 * Author: Chris
 * Date: 
 * License:
 * Source: Yuhao Du and Chinese Paper.
 * Description: Prime sieve for generating all primes up to a certain limit. isprime$[i]$ is true iff $i$ is a prime.
 * Also useful if you need to compute any multiplicative function (in this case Moebius..).
 * Status: Works
 * Time: 
 */
#pragma once

const int MAX_PR = 5000000;
vector<int> p(MAX_PR), prime(MAX_PR), mu(MAX_PR, -1);
void run_sieve {
	mu[1] = 1;
	int i, j, tot, t1;
	for (i = 1; i <= MAX_PR; ++i) p[i] = i;
	for (i = 2, tot = 0; i <= MAX_PR; ++i){
		if (p[i] == i) prime[++tot] = i;
		for (j = 1; j <= tot && (t1 = prime[j] * i) <= MAX_PR; ++j) {
			p[t1] = prime[j];
			mu[t1] *= mu[i];
			if (i % prime[j] == 0) {
				phi[t1] = phi[i] * prime[j];
				break;
			}
		} 
	}	
}
