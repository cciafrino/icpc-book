#include "../utilities/template.h"
#include "../../content/number-theory/modular-arithmetic.h"

inline int nxt_pow2(int s) { return 1 << (s > 1 ? 32 - __builtin_clz(s-1) : 0); }

template <typename dbl> struct cplx {
    dbl x, y;
    cplx(dbl x_ = 0, dbl y_ = 0) : x(x_), y(y_) { }
    friend cplx operator+(cplx a, cplx b) { return cplx(a.x + b.x, a.y + b.y); }
    friend cplx operator-(cplx a, cplx b) { return cplx(a.x - b.x, a.y - b.y); }
    friend cplx operator*(cplx a, cplx b) { return cplx(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
    friend cplx conj(cplx a) { return cplx(a.x, -a.y); }
    friend cplx inv(cplx a) { dbl n = (a.x*a.x+a.y*a.y); return cplx(a.x/n,-a.y/n); }
};

template <typename T>
struct root_of_unity {};

template <typename dbl> struct root_of_unity<cplx<dbl>> {
    static cplx<dbl> f(int k) {
        static const dbl PI = acos(-1);
        dbl a=2*PI/k;
        return cplx<dbl>(cos(a),sin(a));
    }
};

constexpr int MOD = 998244353;
template<> struct root_of_unity<modnum<MOD>> {
    static constexpr modnum<MOD> g = modnum<MOD>(3);
    static modnum<MOD> f(int k) {
        assert((MOD-1)%k == 0);
        return g.pow((MOD-1)/k);
    }
};

template<typename T>
vector<T> fft(vector<T> p, bool inverse) { // df3434
    int N = p.size();
    vector<T> q(N);
    for (int i = 0; i < N; ++i) {
        int rev = 0;
        for (int b = 1; b < N; b <<= 1) {
            rev = (rev << 1) | !!(i & b);
        }
        q[rev] = p[i];
    }
    swap(p, q);
    for (int b = 1; b < N; b <<= 1) {
        T w = root_of_unity<T>::f(2*b);
        if (inverse) w = T(1) * inv(T(w));
        for (auto [i, x] = std::pair(0, T(1)); i < N; ++i, x = x * w) {
            q[i] = p[i & ~b] + x * p[i | b];
        }
        swap(p, q);
    }
    if (inverse) {
        auto v = T(N), iv = inv(v);
        T inv = T(1) * iv;
        for (int i = 0; i < N; ++i) p[i] = p[i] * inv;
    }
    return p;
}

constexpr int threshold = 64;

template<typename T>
vector<T> operator*(vector<T> p, vector<T> q) {
    int N = p.size(), M = q.size();
    int K = N + M - 1, S = nxt_pow2(K);
    vector<T> res(K);
    if (min(N, M) <= threshold) {
        for (int a = 0; a < N; ++a) 
            for (int b = 0; b < M; ++b) 
                res[a + b] = res[a + b] + p[a] * q[b];
    } else {
        p.resize(S), q.resize(S);
        auto phat = fft(std::move(p), false);
        auto qhat = fft(std::move(q), false);
        for (int i = 0; i < S; ++i) {
            phat[i] = phat[i] * qhat[i];
        }
        res = fft(std::move(phat), true);
        res.resize(K);
    }
    return res;
}
using vd = vector<double>;

int ra() {
    static unsigned X;
    X *= 123671231;
    X += 1238713;
    X ^= 1237618;
    return (X >> 1);
}

const double EPS = 1e-8;
using num = modnum<998244353>;
int main() {
    mt19937 rng(48);
    std::uniform_real_distribution<> dis(-5000, 5000);
    // over reals
    {
        vector<cplx<double>> a, b;
        rep(it,0,6000) {
            a.resize(ra() % 100);
            b.resize(ra() % 100);
            for(auto &x: a) x = dis(rng) / (5000 + 1.0) * 10 - 5;
            for(auto &x: b) x = dis(rng) / (5000 + 1.0) * 10 - 5;
            
            auto res = a * b;

            rep(i,0,a.size() + b.size() - 1) {
                cplx<double> sum;
                rep(j,0,a.size()) if (i - j >= 0 && i - j < b.size()) {
                    sum = sum + a[j] * b[i - j];
                }   
                auto v = res[i].x; 
                // cout << sum.x << "  <-->  "<< res[i].x << endl;
                assert(abs(sum.x - v) < EPS);
            }
        }
    }
    // over a finite field
    {
        vector<num> a, b;
        rep(it,0,6000) {
            a.resize(ra() % 100);
            b.resize(ra() % 100);
            for(auto &x: a) x = ra();
            for(auto &x: b) x = ra();
            
            auto res = a * b;

            rep(i,0,a.size() + b.size() - 1) {
                num sum;
                rep(j,0,a.size()) if (i - j >= 0 && i - j < b.size()) {
                    sum = sum + a[j] * b[i - j];
                }   
                auto v = res[i]; 
                // cout << sum.x << "  <-->  "<< res[i] << endl;
                assert((sum.x - v) == 0);
            }
        }
    }
    
    cout<<"Tests passed!"<<endl;
}

