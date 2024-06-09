/**
 * Author: Chris
 * Date: 2023
 * License: 
 * Source: 
 * Description: implementation of crt (naive and garner) to convolute polynomials under arbitrary Fields.
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for $N=2^{22}$)
 */

// T = {unsigned, unsigned long long, modnum<M>}
// Remark: need to satisfy |poly| * mod^2 < \prod_{i} M_i
template<class T, unsigned M0, unsigned M1, unsigned M2, unsigned M3, unsigned M4>
T garner(modnum<M0> a0, modnum<M1> a1, modnum<M2> a2, modnum<M3> a3, modnum<M4> a4) { ///start-hash
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
// results must be in [-448002610255888384, 448002611254132736]
vector<ll> convolve(const vector<ll>& as, const vector<ll>& bs) {///start-hash
	static constexpr unsigned M0 = M0::M, M1 = M1::M;
	static const modnum<M1> INV_M0_M1 = modnum<M1>(M0).inv();
	if (as.empty() || bs.empty()) return {};
	const int len_as = int(as.size()), len_bs = int(bs.size());
	vector<modnum<M0>> as0(len_as), bs0(len_bs);
	for (int i = 0; i < len_as; ++i) as0[i] = as[i];
	for (int i = 0; i < len_bs; ++i) bs0[i] = bs[i];
	const vector<modnum<M0>> cs0 = FFT0.convolve(as0, bs0);
	vector<modnum<M1>> as1(len_as), bs1(len_bs);
	for (int i = 0; i < len_as; ++i) as1[i] = as[i];
	for (int i = 0; i < len_bs; ++i) bs1[i] = bs[i];
	const vector<modnum<M1>> cs1 = FFT1.convolve(as1, bs1);
	vector<ll> cs(len_as + len_bs - 1);
	for (int i = 0; i < len_as + len_bs - 1; ++i) {
		const modnum<M1> d1 = INV_M0_M1 * (cs1[i] - cs0[i].x);
		cs[i] = (d1.x > M1 - d1.x)
			? (-1ULL - (static_cast<unsigned ll>(M1 - 1U - d1.x) * M0 + (M0 - 1U - cs0[i].x)))
			: (static_cast<unsigned ll>(d1.x) * M0 + cs0[i].x);
	}
	return cs;
}///end-hash