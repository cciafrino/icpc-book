/**
 * Author: Chris
 * Description: Every even integer greater than 2 can be expressed as 
 * the sum of two primes.
 */
vector<pair<int, int>> Goldbach(int n){
    int ret = 0;
    for(int i = 2; i <= n/2; ++i)
        if (primes[i] && primes[n-i])
               g.emplace_back(i, n-i);
    return g;
}
