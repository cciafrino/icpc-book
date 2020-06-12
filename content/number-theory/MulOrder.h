/**
 * Author: Chris
 * Description: Find the smallest integer $k$ such that $a^k$
 * (mod $m$) $= 1$. $0 < k < m$.
 * Time: close to $O(log(N))$
 * Status: yet to be stress tested 
 */
#include<Sieve.h>
#include<Divisors.h>
#include<PrimeFactors.h>
#include<Modpow.h>

template<typename T> T mulOrder(T a, T m) {
    auto pf = prime_factorize(m);
    T res = 1;
    for (auto &[p, e] : pf) {
    	T k = 0, q = Pow(p, e);
    	T t = q / p * (p - 1);
    	auto factors = divisors(t);
    	for (auto &pr : factors) 
	        if (modpow(a, pr, m) == 1) {
	        	k = pr;
	        	break;
	        }
    	res = res/__gcd(res, k) * k;
    }
    return res;
}
