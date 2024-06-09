#include "../utilities/template.h"

mt19937 rng(48);
std::uniform_real_distribution<> dis(-5000, 5000);

using vd = vector<double>;

int ra() {
    static unsigned X;
    X *= 123671231;
    X += 1238713;
    X ^= 1237618;
    return (X >> 1);
}

const double EPS = 1e-8;
#include "../../content/number-theory/modular-arithmetic.h"
using num = modnum<998244353>;
using M0 = modnum<998244353>;
using M1 = modnum<998244353>;

namespace test_complex {
#include "../../content/numerical/root-of-unity.h"
#include "../../content/numerical/fast-fourier-transform.h"
void solve0() {
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
}

namespace test_zp {
#include "../../content/numerical/root-of-unity-zp.h"
#include "../../content/numerical/fast-fourier-transform.h"
FFT<M0> FFT0;
FFT<M1> FFT1;
void solve1() {
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
}

int main() {
    // over reals
    {
		test_complex::solve0();
    }
    // over a finite field
    {
		test_zp::solve1();
    }
    
    cout<<"Tests passed!"<<endl;
}

