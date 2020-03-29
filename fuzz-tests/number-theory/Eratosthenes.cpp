#include "../utilities/template.h"

struct prime_sieve {
	typedef unsigned char uchar;
	typedef unsigned int uint;
	static const int pregen = 3*5*7*11*13;
	uint n, sqrtn;
	uchar *isprime;
	int *prime, primes; // prime[i] is i:th prime

	bool is_prime(int n) { // primality check
		if(n%2==0 || n<=2) return n==2;
		return isprime[(n-3)>>4] & 1 << ((n-3) >> 1&7);
	}

	prime_sieve(int _n) : n(_n), sqrtn((int)ceil(sqrt(1.0*n))) {
		int n0 = max(n>>4, (uint)pregen) + 1;
		prime = new int[max(2775, (int)(1.12*n/log(1.0*n)))];
		prime[0]=2; prime[1]=3; prime[2]=5;
		prime[3]=7; prime[4]=11; prime[5]=13;
		primes=6;
		isprime = new uchar[n0];
		memset(isprime, 255, n0);

		for(int j=1,p=prime[j];j<6;p=prime[++j])
			for(int i=(p*p-3)>>4,s=(p*p-3)>>1&7;
				i<=pregen; i+= (s+=p)>>3, s&=7)
					isprime[i] &= (uchar)~(1<<s);
		for(int d=pregen, b=pregen+1; b<n0; b+=d,d<<=1)
			memcpy(isprime+b,isprime+1,(n0<b+d)?n0-b:d);
		for(uint p=17,i=0,s=7; p<n; p+=2, i+= ++s>>3, s&=7)
			if(isprime[i]&1<<s) {
				prime[primes++] = p;
				if(p<sqrtn) {
					int ii=i, ss=s+(p-1)*p/2;
					for(uint pp=p*p; pp<n; pp+=p<<1, ss+=p) {
						ii += ss>>3;
						ss &=7;
						isprime[ii] &= (uchar)~(1<<ss);
}	}		}	}	}; 


#include "../../content/number-theory/eratosthenes.h"
#include "../../content/number-theory/LinearSieve.h"

vector<int> mu2, lp;
void run_sieve2(int n) {
    mu2.assign(n+1, -1);
    lp.assign(n+1, 0);
    mu2[1] = 1;
    vector<int> prime;
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i; 
            prime.push_back(i);
        }
        for (int p : prime) {
            if (p > lp[i] || i * p > n) break;
            if (i % p == 0) mu2[i*p] = 0;
            lp[i * p] = p;
            mu2[i * p] *= mu2[i];
        } 
    }
}

int main(int argc, char** argv) {
	ll s = 0, s2 = 0;   
	// prime_sieve ps(MAX_PR);
	// rep(i,0,ps.primes) s += ps.prime[i];
	
	double mine = 0, xudyh = 0, tourist = 0;

	auto start_mine = chrono::high_resolution_clock::now();
	// vi r = run_sieve(MAX_PR);
	run_sieve2(MAX_PR);
	auto end_mine = chrono::high_resolution_clock::now();
	mine = chrono::duration_cast<chrono::nanoseconds>(end_mine - start_mine).count();
	mine *= 1e-9;

	// trav(x, r) s2 += x;
	
	auto start_xudyh = chrono::high_resolution_clock::now();
	vector<int> p(MAX_PR), prime(MAX_PR), phi(MAX_PR+1), mu(MAX_PR, -1);
	int i, j, tot, t1;
	for (i = 1; i <= MAX_PR; ++i) p[i] = i, phi[i+1] = i;
	mu[1] = phi[1] = 1;
	for (i = 2, tot = 0; i <= MAX_PR; ++i){
		if (p[i] == i) prime[++tot] = i;
		for (j = 1; j <= tot && (t1 = prime[j] * i) <= MAX_PR; ++j){
			p[t1] = prime[j];
			mu[t1] *= mu[i];
			phi[t1] = phi[i] * phi[prime[j]];
			if (i % prime[j] == 0) {
				mu[t1] = 0;
				phi[t1] = phi[i] * prime[j];
				break;
			}
		} 
	}
	auto end_xudyh = chrono::high_resolution_clock::now();
	xudyh = chrono::duration_cast<chrono::nanoseconds>(end_xudyh - start_xudyh).count(); 
	xudyh *= 1e-9;
	// for (int u : phi) cout << u << endl; 
 	//   	trav(x, prime) s += x;
	// // auto start_tourist = chrono::high_resolution_clock::now();
	// // LinearSieve(MAX_PR);
	// // auto end_tourist = chrono::high_resolution_clock::now();
	// tourist = chrono::duration_cast<chrono::nanoseconds>(end_tourist - start_tourist).count(); 
	// tourist *= 1e-9;
	// cout << s << ' ' << s2 << endl;
	// assert(s==s2);
	cout<<"Tests passed!"<<endl;
	cout << "Mine: " << mine << endl;
	cout << "Xudyh's: " << xudyh << endl;
	// cout << "Tourist's: " << tourist  << endl;
}
