#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T>
T egcd(T a, T b, T &x, T &y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    T p = b / a;    
    T g = egcd(b - p * a, a, y, x);
    x -= y * p;
    return g;
}
template<typename T>
T crt(T a, T m, T b, T n) { /// start-hash
	if (n > m) swap(a, b), swap(m, n);
	T x, y, g = egcd(m, n, x, y);
	assert((a - b) % g == 0); // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}/// end-hash


ll rmod(ll a, ll b) { return (a % b + b) % b; }

std::mt19937_64 rng(2);

ll randExp() {
	int e = rand() % 63; // 64
	return uniform_int_distribution<ll>(0, (ll)((1ULL << e) - 1))(rng);
}
ll mul(ll a,ll b,ll m){
    if(b == 0)
        return 0;
    ll t = mul(a,b/2,m);
    t = (t+t)%m;
    if(b&1)
        t = (t+a)%m;
    return t;
}
 
ll exp(ll a,ll b,ll m){
    if(b == 0)
        return 1;
    ll t = exp(a,b/2,m);
    t = mul(t,t,m);
    if(b&1)
        t = mul(t,a,m);
    return t;
}

ll crt2(ll a1,ll m1,ll a2,ll m2){
    ll g = __gcd(m1,m2);
    if(a1%g != a2%g)
        return -1;
    m2 /= g;
    a2 %= m2;
    ll phi = m2;
    
    int aux = m2;
    for(int i=2;i*i<=aux;i++)
        if(aux%i == 0){
            while(aux%i == 0)
                aux /= i;
            phi /= i;
            phi *= (i-1);
        }
    if(aux > 1){
        phi /= aux;
        phi *= (aux-1);
    }
    
    ll ans = a1 + mul(a2-a1,exp(m1,phi,m1*m2),m1*m2);
    ans %= (m1*m2);
    if(ans < 0) ans += m1*m2;
    
    return ans;
}

template<typename T>
T crt3(T a1, T m1, T a2, T m2) {
	if (m2 > m1) {
		swap(a1, a2);
		swap(m1, m2);
	}
	T x, y, g = egcd(m1, m2, x, y);
	if ((a1 - a2) % g != 0) return -1;
	x = (a2 - a1) % m2 * x % m2 / g * m1 + a1;
	if (x < 0) 
		return x + m1 * m2/g;
	else return x;
}
 
ll x ,y;

int main(int argc, char** argv) {
	rep(it,0,10000000) {
		ll a = randExp() * (rand() % 2 ? 1 : -1);
		ll b = randExp() * (rand() % 2 ? 1 : -1);
		ll m = randExp() + 1;
		ll n = randExp() + 1;
		ll g = __gcd(m, n);
		if (n * (__int128_t)m > LLONG_MAX) continue;
		if (n * (__int128_t)m > (1LL << 62) && (abs(a) > m || abs(b) > n)) continue;
		if ((a - b) % g == 0) {
			//ll r = crt(a, m, b, n, x, y);
			ll r = crt3(a, m, b, n);
			if (rmod(r, m) != rmod(a, m) || rmod(r, n) != rmod(b, n)) {
				cout << a << endl;
				cout << b << endl;
				cout << m << endl;
				cout << n << endl;
			}
			assert(rmod(r, m) == rmod(a, m));
			assert(rmod(r, n) == rmod(b, n));
			if (-m < a && a < m && -n < b && b < n) {
				assert(0 <= r);
				assert(r < m*n/g);
			}
		}
	}
	cout<<"Tests passed!"<<endl;
}