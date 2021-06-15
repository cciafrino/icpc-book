/**
 * Author: Chris
 * Date: 2016-07-24
 * License: CC0
 * Source: 
 * Description: Calculate the order of $a$ in $Z_n$. A group $Z_n$ is cyclic if, and only if n = $1, 2, 4, p^k$ or $2 p^k$, being $p$ an odd prime number.
 * Status: Works
 * Time: $O(sqrt(n)log(n))$
 */
template<typename T> T order(T a, T n) {
    vector<T> d = divisors(phi(n)); // divisors returns vector
    for (int i : v)                 // with all divisors of phi(n)
        if (modpow(a, i, n) == 1) return i;
    return -1;
}
