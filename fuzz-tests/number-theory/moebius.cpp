#include<bits/stdc++.h>
using namespace std;

using lint = long long;

vector<int> lp, primes, mu;
void run_sieve(int n) {
	lp.resize(n); primes.resize(n); mu.assign(n, -1);
	mu[1] = 1;
	int i, j, tot, t1;
	for (i = 1; i <= n; ++i) lp[i] = i;
	for (i = 2, tot = 0; i <= n; ++i){
		if (lp[i] == i) primes[++tot] = i;
		for (j = 1; j <= tot && (t1 = primes[j] * i) <= n; ++j) {
			lp[t1] = primes[j];
			mu[t1] *= mu[i];
			if (i % primes[j] == 0) {mu[t1] = 0; break;}
		} 
	}	
}

template<typename T> T mobius(T n) {
    T p = 0, aux = n;
    for (int i = 2; i*i <= n; ++i)
        if (n % i == 0) {
            n /= i;
            p += 1;
            if (n % i == 0) return 0;
        }
    return (p&1 || n == 1? 1 : -1);
}


int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    run_sieve(1001000);

    for(int i = 1; i <= 1000000; ++i) {
    	assert(mu[i] == mobius(i));
    	// cout << i <<": " << mobius(i) << endl;
    }
    cout << "Tests passed!" << endl;
}