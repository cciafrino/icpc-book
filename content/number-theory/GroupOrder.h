/**
 * Author: Chris
 * Date: 2016-07-24
 * License: CC0
 * Source: 
 * Description: Calculate the order of $a$ in $Z_n$. A group $Z_n$ is cyclic if, and only if n = $1, 2, 4, p^k$ or $2 p^k$, being $p$ an odd prime number.
 * Status: Works
 * Time: $O(sqrt(n)log(n))$
 */

vector<int> divisors(int n) {
    vector<int> result, aux;
    for (int i = 1; i*i <= n; ++i) {
        if (n % i == 0) {
            result.push_back(i);
            if (i*i != n) aux.push_back(n/i);
        }
    }
    for (int i = aux.size()-1; i+1; --i) result.push_back(aux[i]);
    return result;
}

template<typename T>
T order(T a, T n) {
    vector<T> d = divisors(phi(n));
    for (int i : v) 
        if (mod_pow(a, i, n) == 1) return i;
    return -1;
}
