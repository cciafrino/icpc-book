#include "../utilities/template.h"
#include "../../content/number-theory/modular-arithmetic.h"
template <typename dbl> struct cplx { ///start-hash
	dbl x, y; using P = cplx;
	cplx(dbl x_ = 0, dbl y_ = 0) : x(x_), y(y_) { }
	friend P operator+(P a, P b) { return P(a.x+b.x, a.y+b.y); }
	friend P operator-(P a, P b) { return P(a.x-b.x, a.y-b.y); }
	friend P operator*(P a, P b) { return P(a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x); }
	friend P conj(P a) { return P(a.x, -a.y); }
	friend P inv(P a) { dbl n = (a.x*a.x+a.y*a.y); return P(a.x/n,-a.y/n); }
};
template <typename T> struct root_of_unity {};
template <typename dbl> struct root_of_unity<cplx<dbl>> {
	static cplx<dbl> f(int k) {
		static const dbl PI = acos(-1); dbl a = 2*PI/k;
		return cplx<dbl>(cos(a),sin(a));
	}
}; ///end-hash
inline int nxt_pow2(int s) { return 1 << (s > 1 ? 32 - __builtin_clz(s-1) : 0); }

//(MOD,3) := (M1:897581057),(M3:985661441),(M5:935329793)
using M0 = modnum<998244353U>;///start-hash
constexpr unsigned primitive_root(unsigned M) {
	if (M == 880803841U) return 26U; // (M2)
	else if (M == 943718401U) return 7U; // (M4)
	else if (M == 918552577U) return 5U; // (M6)
	else return 3U;
}
template<unsigned MOD> struct root_of_unity<modnum<MOD>> {
	static constexpr modnum<MOD> g0 = primitive_root(MOD);
	static modnum<MOD> f(int K) {
		assert((MOD-1)%K == 0); return g0.pow((MOD-1)/K);
	}
};///end-hash
template<typename T> struct FFT {
	vector<T> rt; vector<int> rev;
	FFT() : rt(2, T(1)) {}
	void init(int N) {///start-hash
		N = nxt_pow2(N);
		if (N > int(rt.size())) {
			rev.resize(N); rt.reserve(N);
			for (int a = 0; a < N; ++a)
				rev[a] = (rev[a/2] | ((a&1)*N)) >> 1;
			for (int k = int(rt.size()); k < N; k *= 2) {
				rt.resize(2*k);
				T z = root_of_unity<T>::f(2*k);
				for (int a = k/2; a < k; ++a)
					rt[2*a] = rt[a], rt[2*a+1] = rt[a] * z;
			}
		}
	}///end-hash
	void fft(vector<T>& xs, bool inverse) const {///start-hash
		int N = int(xs.size());
		int s = __builtin_ctz(int(rev.size())/N);
		if (inverse) reverse(xs.begin() + 1, xs.end());
		for (int a = 0; a < N; ++a) {
			if (a < (rev[a] >> s)) swap(xs[a], xs[rev[a] >> s]);
		}
		for (int k = 1; k < N; k *= 2) {
			for (int a = 0; a < N; a += 2*k) {
				int u = a, v = u + k;
				for (int b = 0; b < k; ++b, ++u, ++v) {
					T z = rt[b + k] * xs[v];
					xs[v] = xs[u] - z, xs[u] = xs[u] + z;
				}
			}
		}
		if (inverse)
			for (int a = 0; a < N; ++a) xs[a] = xs[a] * inv(T(N));
	}///end-hash
	vector<T> convolve(vector<T> as, vector<T> bs) {///start-hash
		int N = int(as.size()), M = int(bs.size());
		int K = N + M - 1, S = nxt_pow2(K); init(S);
		if (min(N, M) <= 64) {
			vector<T> res(K);
			for (int u = 0; u < N; ++u) for (int v = 0; v < M; ++v)
				res[u + v] = res[u + v] + as[u] * bs[v];
			return res;
		} else {
			as.resize(S), bs.resize(S);
			fft(as, false); fft(bs, false);
			for (int i = 0; i < S; ++i) as[i] = as[i] * bs[i];
			fft(as, true); as.resize(K); return as;
		}
	}///end-hash
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

         FFT<cplx<double>> fft_data;
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

         FFT<modnum<998244353>> fft_data;
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

