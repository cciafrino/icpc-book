/**
 * Author: Andrei Navumenka, chilli
 * Date: 2019-11-08
 * License: Unlicense
 * Source: https://github.com/indy256/codelibrary/blob/master/cpp/numbertheory/discrete_log.cpp
 * Description: Calculates the discrete log. Returns an x s.t. a^x = b mod m. a and m must be coprime.
 * Time: $O(n^{1/2})$
 * Status: tested for all values under a 1000 for a,x, and m.
 */

lint modLog(lint a, lint b, lint m) {
    assert(__gcd(a, m) == 1);
    lint n = (lint) sqrt(m) + 1, an = 1;
    for(int i = 0; i < n; ++i) an = an * a % m;
    unordered_map<lint, lint> vals;
    for (lint i = 1, x = an; i <= n; i++, x = x * an % m)
        if (!vals.count(x)) vals[x] = i;
    for (lint i = 0, x = b; i <= n; i++, x = x * a % m)
        if (vals.count(x)) {
            lint res = vals[x] * n - i;
            if (res < m) return res;
        }
    return -1;
}