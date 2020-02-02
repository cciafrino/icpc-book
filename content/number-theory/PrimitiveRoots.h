/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: 
 * Description: That is, 
 * $g$ is a primitive root mod $n$ if for every number $x$ coprime to $n$
 * there is an integer $z$ s.t. $x \equiv g^z  \pmod{n}$
 * Status: 
 * Time: 
 */

template<typename T>
T primitive_roots(T p) {
    T n = p - 1;
    vector<T> factors;
    for (int i = 2; i*i <= n; ++i) if (n % i == 0) {
        factors.push_back(i);
        while (n % i == 0) n /= i;
    }
    if (n > 1) factors.push_back(n);
    for (int i = 2; i <= p; ++i) {
        bool works = true;
        for (int j = 0; j < factors.size() && works; ++j) 
            works &= modpow(i, (p-1)/factors[i], p) != 1;
        if (works) return i;
    }
    return -1;
}
