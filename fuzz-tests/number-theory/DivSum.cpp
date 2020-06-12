#include<bits/stdc++.h>
using namespace std;

using lint = long long;

lint Pow(lint b, lint e) {
	lint ret = 1;
	for (int i = 1; i <= e; i <<= 1, b = b * b)
		if (i & e) ret = ret * b;
	return ret;
}

vector<pair<int, int>> factorize(int value) {
    vector<pair<int, int>> result;
    for (int p = 2; p*p <= value; ++p)
        if (value % p == 0) {
            int exp = 0;
            while (value % p == 0) {
                value /= p;
                ++exp;
            }
            result.emplace_back(p, exp);
        }
    if (value != 1) {
        result.emplace_back(value, 1);
        value = 1;
    }
    return result;
}

vector<int> lp, primes;
void run_sieve(int n) {
    lp.resize(n); primes.resize(n); 
    int i, j, tot, x;
    for (i = 1; i <= n; ++i) lp[i] = i;
    for (i = 2, tot = 0; i <= n; ++i){
        if (lp[i] == i) primes[++tot] = i;
        for (j = 1; j <= tot && (x = primes[j]*i) <= n; ++j) {
            lp[x] = primes[j];
            if (i % primes[j] == 0) break;
        } 
    }   
}

lint divsum(int x) {
    lint sum = 1;
    int p, f;
    while(x > 1) {
        for (p = lp[x], f = 0; (x > 1) && (p == lp[x]); x /= p) f++;
        sum *= (Pow(p, f + 1) - 1)/(p - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    run_sieve(100000000);
    for (int i = 0; i < 10000; ++i) {
    	int n = rng() % 100000000;
    	auto factors = factorize(n);
    	lint res = 1;
    	for (auto [p, e] : factors) {
    		res *= (Pow(p, e+1) - 1)/(p - 1);
    	}
        lint ret = divsum(n);
        assert(res == ret);
    }
    cout << "Tests passed!" << endl;

}