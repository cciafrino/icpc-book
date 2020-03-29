// #include "../utilities/template.h"
#include<bits/stdc++.h>
using namespace std;
using lint = long long;
#include "../../content/number-theory/PollardRho.h"

#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef double db;
mt19937 mrand(random_device{}()); 
const ull mod=1000000007;
int rnd(int x) { return mrand() % x;}
ull powmod(ull a,ull b) {ull res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ull gcd(ull a,ull b) { return b?gcd(b,a%b):a;}
// head
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<typename T>
struct Factorizer {
    const int N = 1010000;
    T C, n, mut, a[1001000];
    vector<T> factors, _e, _pr, d;
    vector<int> prime, p;
    int Q, cnt, i, l, psize, _cnt;
    Factorizer(int n) : psize(n), factors(10010), prime(N),
        p(N), _e(100), _pr(100) { run_sieve(); }
    inline T mul(T a, T b, T p) {
        if (p <= 1000000000) return a * b % p;
        else if (p <= 1000000000000ll) return (((a*(b>>20)%p)<<20)+(a*(b&((1<<20)-1))))%p;
        else {
            T d = (T)floor(a*(long double)b/p+0.5);
            T ret = (a*b - d*p) % p;
            if (ret < 0) ret += p;
            return ret;
        }
    }
    void run_sieve(){
        int i, j, tot, t1;
        for (i = 1; i <= psize; ++i) p[i] = i;
        for (i = 2, tot = 0; i <= psize; ++i){
            if (p[i] == i) prime[++tot] = i;
            for (j = 1; j <= tot && (t1 = prime[j] * i) <= psize; ++j){
                p[t1] = prime[j];
                if (i % prime[j] == 0) break;
            }
        }
    }
    T Pow(T a, T n, T p) {
        T ans = 1;
        for (;n; n >>= 1) {
            if (n&1) ans = mul(ans, a, p);
            a = mul(a, a, p);
        }
        return ans;
    }
    bool witness(T a, T n) {
        int t = 0;
        T u = n-1;
        for (; ~u&1; u >>= 1) t++;
        T x = Pow(a, u, n), _x=0;
        for (; t; t--) {
            _x = mul(x, x, n);
            if (_x == 1 && x != 1 && x != n-1) return 1;
            x = _x;
        }
        return _x != 1;
    }
    bool miller(T n) {
        if (n < 2) return 0;
        if (n <= psize) return p[n] == n;
        if (~n&1) return 0;
        for (int j = 0; j < 8; ++j) if (witness(rng()%(n-1)+1,n)) return 0;
        return 1;
    }
    T gcd(T a, T b) {
        T ret = 1;
        while (a) {
            if ((~a&1) && (~b&1)) ret <<= 1, a >>= 1, b >>= 1;
            else if (~a&1) a >>= 1; else if (~b&1) b >>= 1;
            else {
                if (a < b) swap(a, b);
                a -= b;
            }
        }
        return ret * b;
    }
    T rho(T n) {
        while (true) {
            T X = rng() % n, Y, Z, Q = 1, *lY = a, *lX = lY;
            int tmp = 20;
            C = rng() % 10 + 3;
            X = mul(X, X, n) + C; *(lY++) = X; lX++;
            Y = mul(X, X, n) + C; *(lY++) = Y;
            while (X != Y) {
                T t = X-Y+n;
                Z = mul(Q, t, n);
                if (Z == 0) return gcd(Q, n);
                tmp--;
                if (tmp == 0) {
                    tmp = 20;
                    Z = gcd(Z, n);
                    if (Z != 1 && Z != n) return Z;
                }
                Q = Z;
                Y = *(lY++) = mul(Y,Y,n) + C;
                Y = *(lY++) = mul(Y,Y,n) + C;
                X = *(lX++);
            }
        }
    }
    void _factor(T n) {
        for (int i = 0; i < cnt; i++) {
            if (n % factors[i] == 0) n /= factors[i], factors[cnt++] = factors[i];}
        if (n <= psize) {
            for (;n != 1; n /= p[n]) factors[cnt++] = p[n];
            return;
        }
        if (miller(n)) factors[cnt++] = n;
        else {
            T x = rho(n);
            _factor(x); _factor(n/x);
        }
    }
    void dfs(T x, int depth) {
        if (depth ==_cnt) d.push_back(x);
        else {
            dfs(x, depth + 1);
            for (int i = 1; i <= _e[depth]; i++) dfs(x *= _pr[depth], depth+1);
        }
    }
    void norm() {
        sort(factors.begin(), factors.begin() + cnt);
        _cnt = 0;
        rep(i,0,cnt) if (i == 0 || factors[i] != factors[i-1]) 
            _pr[_cnt] = factors[i], _e[_cnt++] = 1;
            else _e[_cnt-1]++;
    }
    vector<T> getd() {
        d.clear();
        dfs(1, 0);
        return d;
    }
    vector<T> factor(T n) {
        cnt = 0;
        _factor(n); norm();
        return getd();
    }
    vector<pair<T,T>> factorG(T n) {
        cnt = 0;
        _factor(n);
        norm();
        vector<pair<T,T>> d;
        rep(i,0,_cnt) d.push_back({_pr[i], _e[i]});
        return d;
    }
    bool is_primitive(T a,T p) {
        assert(miller(p));
        vector<pair<T, T>> D = factorG(p-1);
        rep(i,0,SZ(D)) if (Pow(a,(p-1)/D[i].first, p) == 1) return 0;
        return 1;
    }
};

mt19937 uni(time(0));
const int ITERS=1e6;
void isValid(ull N, vector<ull> prFac){
    ull cur=1;
    for (auto i: prFac){
        if (!isPrime(i)){
            cout<<N<<endl;
            cout<<i<<endl;
            assert(isPrime(i));
        }
        cur *= i;
    }
    if (cur!= N)
        cout<<cur<<' '<<N<<endl;
    assert(cur == N);
}
int main() {
    
    long double xudyh = 0, kactl = 0;
    assert(factor(1).empty());
    assert(factor(2) == vector<ull>{2});
    Factorizer<ull> f(1000000);
    rep(n,2,1e6) {
        auto start_kactl = chrono::high_resolution_clock::now();
        auto res = factor(n);
        auto end_kactl = chrono::high_resolution_clock::now();

        auto start_xudyh = chrono::high_resolution_clock::now();
        auto res2 = f.factor(n);
        auto end_xudyh = chrono::high_resolution_clock::now();

        xudyh += chrono::duration_cast<chrono::nanoseconds>(end_xudyh - start_xudyh).count(); 
        kactl += chrono::duration_cast<chrono::nanoseconds>(end_kactl - start_kactl).count(); 
        // isValid(n, res2);
        // isValid(n, res);
    }
    rep(i,2,ITERS) {
        ull n = 1 + (uni()%(1ul<<50));
        auto start_kactl = chrono::high_resolution_clock::now();
        auto res = factor(n);
        auto end_kactl = chrono::high_resolution_clock::now();

        auto start_xudyh = chrono::high_resolution_clock::now();
        auto res2 = f.factor(n);
        auto end_xudyh = chrono::high_resolution_clock::now();

        xudyh += chrono::duration_cast<chrono::nanoseconds>(end_xudyh - start_xudyh).count(); 
        kactl += chrono::duration_cast<chrono::nanoseconds>(end_kactl - start_kactl).count(); 
        // isValid(n, res2);
        // isValid(n, res);
    }
    xudyh *= 1e-9;
    kactl *= 1e-9;
    cout<<"Prime Factoring tests passed!"<<endl;
    cout << "Xudyh: " << xudyh << endl;
    cout << "Kactl: " << kactl << endl;
}
