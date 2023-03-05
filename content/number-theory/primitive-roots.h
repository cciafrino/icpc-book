/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: 
 * Description: $a$ is a primitive root mod $n$ if for every number $x$ coprime to $n$
 * there is an integer $z$ s.t. $x \equiv a^z  \pmod{n}$. The number of primitive roots mod n, if
 * there are any, is equal to $phi(phi(N))$. If $m$ isnt prime, replace $m-1$ by $phi(m)$.
 * Status: 
 * Time: $O(log(N))$
 */
#include<sieve.h>
#include<prime-factors.h>
#include<mod-pow.h>

template<typename T> bool is_primitive(T a, T m) {
    vector<pair<T, T>> D = prime_factorize(m-1);
    for (auto p : D) 
        if (modpow(a, (m-1)/p.first, m) == 1) return false;
    return true;
}
