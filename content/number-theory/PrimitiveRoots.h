/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: 
 * Description: $a$ is a primitive root mod $n$ if for every number $x$ coprime to $n$
 * there is an integer $z$ s.t. $x \equiv g^z  \pmod{n}$. The number of primitive roots mod n, if
 * there are any, is equal to $phi(phi(N))$
 * Status: 
 * Time: $O(log(N))$
 */
#include<Sieve.h>
#include<PrimeFactors.h>
#include<Modpow.h>

template<typename T> bool is_primitive(T a, T m) {
    vector<pair<T, T>> D = prime_factorize(m-1);
    for(auto [x, y] : D) 
        if (modpow(a, (m-1)/x, m) == 1) return false;
    return true;
}
