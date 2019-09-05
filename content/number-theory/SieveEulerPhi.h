/**
 * Author: Chris
 * Description: Sieve of Euler Totient Function.
 */
const int lim = 100000;
vector<int> phi(lim);
for (int i = 0; i < lim; ++i) phi[i] = i&1 ? i : i/2;
for (int i = 3; i <= lim; i += 2)
    if (phi[i] == i)
        for (int j = i; j <= lim; j += i)
            phi[j] = (phi[j]/i) * (i - 1);
