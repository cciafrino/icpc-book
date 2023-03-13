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

template<typename T> struct FFT {
    vector<T> rt;
    vector<int> rev;
    FFT(int N) : rt(2, T(1)) {
        if (N > int(rt.size())) {
            rev.resize(N);
            for (int a = 0; a < N; ++a) {
                rev[a] = (rev[a>>1] | ((a&1)*N)) >> 1;
            }
            rt.reserve(N);
            for (int k = int(rt.size()); k < N; k *= 2) {
                rt.resize(2*k);
                T z = root_of_unity<T>::f(2*k);
                for (int a = k/2; a < k; ++a) {
                    rt[2*a] = rt[a];
                    rt[2*a+1] = rt[a] * z;
                }
            }
        }
    }
    void fft(vector<T>& xs, bool inverse) const {
        int N = int(xs.size());
        int s = __builtin_ctz(int(rev.size())/N);
        if (inverse) reverse(xs.begin() + 1, xs.end());
        for (int a = 0; a < N; ++a) {
            if (a < (rev[a] >> s))
                swap(xs[a], xs[rev[a] >> s]);
        }
        for (int k = 1; k < N; k *= 2) {
            for (int a = 0; a < N; a += 2*k) {
                int u = a, v = u + k;
                for (int b = 0; b < k; ++b, ++u, ++v) {
                    T z = rt[b + k] * xs[v];
                    xs[v] = xs[u] - z;
                    xs[u] = xs[u] + z;
                }
            }
        }
        if (inverse) {
            for (int a = 0; a < N; ++a)
                xs[a] = xs[a] * inv(T(N));
        }
    }
    vector<T> convolve(vector<T> as, vector<T> bs) const {
        int N = int(as.size()), M = int(bs.size());
        int K = N + M - 1, S = nxt_pow2(K);
        if (min(N, M) <= 64) {
            vector<T> res(K);
            for (int u = 0; u < N; ++u)
                for (int v = 0; v < M; ++v)
                    res[u + v] = res[u + v] + as[u] * bs[v];
            return res;
        } else {
            as.resize(S), bs.resize(S);
            fft(as, false); fft(bs, false);
            for (int i = 0; i < S; ++i) as[i] = as[i] * bs[i];
            fft(as, true);
            as.resize(K);
            return as;
        }
    }
};

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

        const FFT<cplx<double>> fft_data(1 << 20);
        vector<cplx<double>> a, b;
        rep(it,0,6000) {
            a.resize(ra() % 100);
            b.resize(ra() % 100);
            for(auto &x: a) x = dis(rng) / (5000 + 1.0) * 10 - 5;
            for(auto &x: b) x = dis(rng) / (5000 + 1.0) * 10 - 5;
            
            auto res = fft_data.convolve(a, b);

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

        const FFT<modnum<998244353>> fft_data(1 << 20);
        vector<num> a, b;
        rep(it,0,6000) {
            a.resize(ra() % 100);
            b.resize(ra() % 100);
            for(auto &x: a) x = ra();
            for(auto &x: b) x = ra();
            
            auto res = fft_data.convolve(a, b);

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

