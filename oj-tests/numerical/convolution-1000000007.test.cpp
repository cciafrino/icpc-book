#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/number-theory/modular-arithmetic.h"

#include "../../content/numerical/root-of-unity-zp.h"
#include "../../content/numerical/fast-fourier-transform.h"

using M0 = modnum<998244353U>;
using M1 = modnum<897581057U>;
using M2 = modnum<935329793U>;

// T = {unsigned, unsigned long long, modnum<M>}
// Remark: need to satisfy |poly| * mod^2 < \prod_{i} M_i
template<class T, unsigned M0, unsigned M1, unsigned M2>
T garner(modnum<M0> a0, modnum<M1> a1, modnum<M2> a2) { ///start-hash
	static const modnum<M1> INV_M0_M1 = modnum<M1>(M0).inv();
	static const modnum<M2> INV_M0M1_M2 = (modnum<M2>(M0) * M1).inv();
	// static const modnum<M3> INV_M0M1M2_M3 = (modnum<M3>(M0) * M1 * M2).inv();
	// static const modnum<M4> INV_M0M1M2M3_M4 = (modnum<M4>(M0) * M1 * M2 * M3).inv();
	const modnum<M1> b1 = INV_M0_M1 * (a1 - a0.x);
	const modnum<M2> b2 = INV_M0M1_M2 * (a2 - (modnum<M2>(b1.x) * M0 + a0.x));
	// const modnum<M3> b3 = INV_M0M1M2_M3 * (a3 - ((modnum<M3>(b2.x) * M1 + b1.x) * M0 + a0.x));
	// const modnum<M4> b4 = INV_M0M1M2M3_M4 * (a4 - (((modnum<M4>(b3.x) * M2 + b2.x) * M1 + b1.x) * M0 + a0.x));
	return (T(b2.x) * M1 + b1.x) * M0 + a0.x;
	// return (((T(b4.x) * M3 + b3.x) * M2 + b2.x) * M1 + b1.x) * M0 + a0.x;
}///end-hash

FFT<M0> FFT0;
FFT<M1> FFT1;
FFT<M2> FFT2;

using num = modnum<int(1e9) + 7>;
// results must be in [-448002610255888384, 448002611254132736]
vector<num> convolve(const vector<num>& as, const vector<num>& bs) {///start-hash
	static constexpr unsigned M0 = M0::M, M1 = M1::M, M2 = M2::M;
	if (as.empty() || bs.empty()) return {};
	const int len_as = int(as.size()), len_bs = int(bs.size());
	vector<modnum<M0>> as0(len_as), bs0(len_bs);
	for (int i = 0; i < len_as; ++i) as0[i] = as[i].x;
	for (int i = 0; i < len_bs; ++i) bs0[i] = bs[i].x;
	const vector<modnum<M0>> cs0 = FFT0.convolve(as0, bs0);
	vector<modnum<M1>> as1(len_as), bs1(len_bs);
	for (int i = 0; i < len_as; ++i) as1[i] = as[i].x;
	for (int i = 0; i < len_bs; ++i) bs1[i] = bs[i].x;
	const vector<modnum<M1>> cs1 = FFT1.convolve(as1, bs1);
	vector<modnum<M2>> as2(len_as), bs2(len_bs);
	for (int i = 0; i < len_as; ++i) as2[i] = as[i].x;
	for (int i = 0; i < len_bs; ++i) bs2[i] = bs[i].x;
	const vector<modnum<M2>> cs2 = FFT2.convolve(as2, bs2);
	vector<num> cs(len_as + len_bs - 1);
	for (int i = 0; i < len_as + len_bs - 1; ++i) {
		cs[i] = garner<num>(cs0[i], cs1[i], cs2[i]);
	}
	return cs;
}///end-hash

FFT<num> fft;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M;
	
	vector<num> A(N), B(M);
	for (auto& a : A) cin >> a.x;
	for (auto& b : B) cin >> b.x;
	
	auto C = convolve(A, B);
	for (int i = 0; i < N+M-1; ++i) {
		cout << C[i].x << " \n"[i == N+M-2];
	}
}
