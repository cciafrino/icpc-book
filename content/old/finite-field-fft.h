/**
 * Author: Chris
 * Date: 2022
 * License: CC0
 * Source: Yui
 * Description: can be used for convolutions modulo arbitrary integers
 * Inputs must be in $[0, \text{mod})$.
 * Time: O(N \log N), where $N = |A|+|B|$ (twice as slow as NTT or FFT)
 * Status: stress-tested
 */
#include "../number-theory/modular-arithmetic.h"

// M: prime, G: primitive root, 2^K | M - 1
template <unsigned M_, unsigned G_, unsigned K_> struct FFT {
	static constexpr unsigned M = M_, M2 = 2U * M_, G = G_;
	static constexpr int K = K_;
	using num = modnum<M>;
	// 1, 1/4, 1/8, 3/8, 1/16, 5/16, 3/16, 7/16, ...
	num gs[1 << (K - 1)];
	constexpr FFT() : gs() {
		static_assert(K >= 2, "Fft: K >= 2 must hold");
		static_assert(!((M - 1) & ((1 << K) - 1)), "Fft: 2^K | M - 1 must hold");
		gs[0] = 1;
		gs[1 << (K - 2)] = num(G).pow((M - 1) >> K);
		for (int l = 1 << (K - 2); l >= 2; l >>= 1) {
			gs[l >> 1] = gs[l] * gs[l];
		}
		assert((gs[1] * gs[1]).x == M - 1);
		for (int l = 2; l <= 1 << (K - 2); l <<= 1) {
			for (int i = 1; i < l; ++i) {
				gs[l + i] = gs[l] * gs[i];
			}
		}
	}
	void fft(vector<num> &xs) const {
		const int n = int(xs.size());
		assert(!(n & (n - 1)) && n <= 1 << K);
		for (int l = n; l >>= 1; ) {
			for (int i = 0; i < (n >> 1) / l; ++i) {
				for (int j = (i << 1) * l; j < (i << 1 | 1) * l; ++j) {
					const num t = gs[i] * xs[j + l];
					xs[j + l] = xs[j] - t;
					xs[j] += t;
				}
			}
		}
	}
	void inverse_fft(vector<num> &xs) const {
		const int n = int(xs.size());
		assert(!(n & (n - 1)) && n <= 1 << K);
		for (int l = 1; l < n; l <<= 1) {
			reverse(xs.begin() + l, xs.begin() + (l << 1));
		}
		for (int l = 1; l < n; l <<= 1) {
			for (int i = 0; i < (n >> 1) / l; ++i) {
				for (int j = (i << 1) * l; j < (i << 1 | 1) * l; ++j) {
					const num t = gs[i] * (xs[j] - xs[j + l]);
					xs[j] += xs[j + l];
					xs[j + l] = t;
				}
			}
		}
		num invN = num(n).inv();
		for (int i = 0; i < n; ++i) xs[i] *= invN;
	}
	vector<num> convolve(vector<num> as, vector<num> bs) const {
		const int na = int(as.size()), nb = int(bs.size());
		int n = 1;
		for (; n < na + nb - 1; n <<= 1) {}
		as.resize(n); fft(as); 
		bs.resize(n); fft(bs);
		for (int i = 0; i < n; ++i) as[i] *= bs[i];
		inverse_fft(as); as.resize(na + nb - 1);
		return as;
	}
};


// M0 M1 M2 = 789204840662082423367925761 (> 7.892 * 10^26, > 2^89)
// M0 M3 M4 M5 M6 = 797766583174034668024539679147517452591562753 (> 7.977 * 10^44, > 2^149)
const FFT<998244353U, 3U, 23> FFT0;
const FFT<897581057U, 3U, 23> FFT1;
const FFT<880803841U, 26U, 23> FFT2;
const FFT<985661441U, 3U, 22> FFT3;
const FFT<943718401U, 7U, 22> FFT4;
const FFT<935329793U, 3U, 22> FFT5;
const FFT<918552577U, 5U, 22> FFT6;

// T = unsigned, unsigned long long, modnum<M>
// 667bd
template <class T, unsigned M0, unsigned M1, unsigned M2>
T garner(modnum<M0> a0, modnum<M1> a1, modnum<M2> a2) {
	static const modnum<M1> INV_M0_M1 = modnum<M1>(M0).inv();
	static const modnum<M2> INV_M0M1_M2 = (modnum<M2>(M0) * M1).inv();
	const modnum<M1> b1 = INV_M0_M1 * (a1 - a0.x);
	const modnum<M2> b2 = INV_M0M1_M2 * (a2 - (modnum<M2>(b1.x) * M0 + a0.x));
	return (T(b2.x) * M1 + b1.x) * M0 + a0.x;
}
//560d5
template <class T, unsigned M0, unsigned M1, unsigned M2, unsigned M3, unsigned M4>
T garner(modnum<M0> a0, modnum<M1> a1, modnum<M2> a2, modnum<M3> a3, modnum<M4> a4) {
	static const modnum<M1> INV_M0_M1 = modnum<M1>(M0).inv();
	static const modnum<M2> INV_M0M1_M2 = (modnum<M2>(M0) * M1).inv();
	static const modnum<M3> INV_M0M1M2_M3 = (modnum<M3>(M0) * M1 * M2).inv();
	static const modnum<M4> INV_M0M1M2M3_M4 = (modnum<M4>(M0) * M1 * M2 * M3).inv();
	const modnum<M1> b1 = INV_M0_M1 * (a1 - a0.x);
	const modnum<M2> b2 = INV_M0M1_M2 * (a2 - (modnum<M2>(b1.x) * M0 + a0.x));
	const modnum<M3> b3 = INV_M0M1M2_M3 * (a3 - ((modnum<M3>(b2.x) * M1 + b1.x) * M0 + a0.x));
	const modnum<M4> b4 = INV_M0M1M2M3_M4 * (a4 - (((modnum<M4>(b3.x) * M2 + b2.x) * M1 + b1.x) * M0 + a0.x));
	return (((T(b4.x) * M3 + b3.x) * M2 + b2.x) * M1 + b1.x) * M0 + a0.x;
}

// if you plan to square instead of convolve, just 
// remove each occurence of bs vector and change every 
// convolve call for a square. 
// f12a0d
template <unsigned M> vector<modnum<M>> convolve(const vector<modnum<M>> &as, const vector<modnum<M>> &bs) {
	static constexpr unsigned M0 = decltype(FFT0)::M;
	static constexpr unsigned M1 = decltype(FFT1)::M;
	static constexpr unsigned M2 = decltype(FFT2)::M;
	if (as.empty() || bs.empty()) return {};
	const int asLen = int(as.size()), bsLen = int(bs.size());
	vector<modnum<M0>> as0(asLen), bs0(bsLen);
	for (int i = 0; i < asLen; ++i) as0[i] = as[i].x;
	for (int i = 0; i < bsLen; ++i) bs0[i] = bs[i].x;
	const vector<modnum<M0>> cs0 = FFT0.convolve(as0, bs0);
	vector<modnum<M1>> as1(asLen), bs1(bsLen);
	for (int i = 0; i < asLen; ++i) as1[i] = as[i].x;
	for (int i = 0; i < bsLen; ++i) bs1[i] = bs[i].x;
	const vector<modnum<M1>> cs1 = FFT1.convolve(as1, bs1);
	vector<modnum<M2>> as2(asLen), bs2(bsLen);
	for (int i = 0; i < asLen; ++i) as2[i] = as[i].x;
	for (int i = 0; i < bsLen; ++i) bs2[i] = bs[i].x;
	const vector<modnum<M2>> cs2 = FFT2.convolve(as2, bs2);
	vector<modnum<M>> cs(asLen + bsLen - 1);
	for (int i = 0; i < asLen + bsLen - 1; ++i) {
		cs[i] = garner<modnum<M>>(cs0[i], cs1[i], cs2[i]);
	}
	return cs;
}

// mod 2^64
// 363b35
vector<unsigned long long> convolve(const vector<unsigned long long> &as, const vector<unsigned long long> &bs) {
	static constexpr unsigned M0 = decltype(FFT0)::M;
	static constexpr unsigned M3 = decltype(FFT3)::M;
	static constexpr unsigned M4 = decltype(FFT4)::M;
	static constexpr unsigned M5 = decltype(FFT5)::M;
	static constexpr unsigned M6 = decltype(FFT6)::M;
	if (as.empty() || bs.empty()) return {};
	const int asLen = int(as.size()), bsLen = int(bs.size());
	vector<modnum<M0>> as0(asLen), bs0(bsLen);
	for (int i = 0; i < asLen; ++i) as0[i] = as[i];
	for (int i = 0; i < bsLen; ++i) bs0[i] = bs[i];
	const vector<modnum<M0>> cs0 = FFT0.convolve(as0, bs0);
	vector<modnum<M3>> as3(asLen), bs3(bsLen);
	for (int i = 0; i < asLen; ++i) as3[i] = as[i];
	for (int i = 0; i < bsLen; ++i) bs3[i] = bs[i];
	const vector<modnum<M3>> cs3 = FFT3.convolve(as3, bs3);
	vector<modnum<M4>> as4(asLen), bs4(bsLen);
	for (int i = 0; i < asLen; ++i) as4[i] = as[i];
	for (int i = 0; i < bsLen; ++i) bs4[i] = bs[i];
	const vector<modnum<M4>> cs4 = FFT4.convolve(as4, bs4);
	vector<modnum<M5>> as5(asLen), bs5(bsLen);
	for (int i = 0; i < asLen; ++i) as5[i] = as[i];
	for (int i = 0; i < bsLen; ++i) bs5[i] = bs[i];
	const vector<modnum<M5>> cs5 = FFT5.convolve(as5, bs5);
	vector<modnum<M6>> as6(asLen), bs6(bsLen);
	for (int i = 0; i < asLen; ++i) as6[i] = as[i];
	for (int i = 0; i < bsLen; ++i) bs6[i] = bs[i];
	const vector<modnum<M6>> cs6 = FFT6.convolve(as6, bs6);
	vector<unsigned long long> cs(asLen + bsLen - 1);
	for (int i = 0; i < asLen + bsLen - 1; ++i) {
		cs[i] = garner<unsigned long long>(cs0[i], cs3[i], cs4[i], cs5[i], cs6[i]);
	}
	return cs;
}

// Results must be in [-2^63, 2^63).
// 920fee
vector<long long> convolveSmall3(const vector<long long> &as, const vector<long long> &bs) {
	static constexpr unsigned M0 = decltype(FFT0)::M;
	static constexpr unsigned M1 = decltype(FFT1)::M;
	static constexpr unsigned M2 = decltype(FFT2)::M;
	static const modnum<M1> INV_M0_M1 = modnum<M1>(M0).inv();
	static const modnum<M2> INV_M0M1_M2 = (modnum<M2>(M0) * M1).inv();
	if (as.empty() || bs.empty()) return {};
	const int asLen = as.size(), bsLen = bs.size();
	vector<modnum<M0>> as0(asLen), bs0(bsLen);
	for (int i = 0; i < asLen; ++i) as0[i] = as[i];
	for (int i = 0; i < bsLen; ++i) bs0[i] = bs[i];
	const vector<modnum<M0>> cs0 = FFT0.convolve(as0, bs0);
	vector<modnum<M1>> as1(asLen), bs1(bsLen);
	for (int i = 0; i < asLen; ++i) as1[i] = as[i];
	for (int i = 0; i < bsLen; ++i) bs1[i] = bs[i];
	const vector<modnum<M1>> cs1 = FFT1.convolve(as1, bs1);
	vector<modnum<M2>> as2(asLen), bs2(bsLen);
	for (int i = 0; i < asLen; ++i) as2[i] = as[i];
	for (int i = 0; i < bsLen; ++i) bs2[i] = bs[i];
	const vector<modnum<M2>> cs2 = FFT2.convolve(as2, bs2);
	vector<long long> cs(asLen + bsLen - 1);
	for (int i = 0; i < asLen + bsLen - 1; ++i) {
		const modnum<M1> d1 = INV_M0_M1 * (cs1[i] - cs0[i].x);
		const modnum<M2> d2 = INV_M0M1_M2 * (cs2[i] - (modnum<M2>(d1.x) * M0 + cs0[i].x));
		cs[i] = (d2.x > M2 - d2.x)
			? (-1ULL - ((static_cast<unsigned long long>(M2 - 1U - d2.x) * M1 + (M1 - 1U - d1.x)) * M0 + (M0 - 1U - cs0[i].x)))
			: ((static_cast<unsigned long long>(d2.x) * M1 + d1.x) * M0 + cs0[i].x);
	}
	return cs;
}

const FFT<998244353U, 3U, 22> fft_data;
