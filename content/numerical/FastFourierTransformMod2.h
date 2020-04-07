/**
 * Author: chilli
 * Date: 2019-04-25
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
 * Description: Higher precision FFT, can be used for convolutions modulo arbitrary integers
 * as long as $N\log_2N\cdot \text{mod} < 8.6 \cdot 10^{14}$ (in practice $10^{16}$ or higher).
 * Inputs must be in $[0, \text{mod})$.
 * Time: O(N \log N), where $N = |A|+|B|$ (twice as slow as NTT or FFT)
 * Status: somewhat tested
 */
#include "FastFourierTransform.h"

typedef vector<lint> vl;
template<int M> vl convMod(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	vl res(a.size() + b.size() - 1);
	int B=32-__builtin_clz(res.size()), n=1<<B, cut=int(sqrt(M));
	vector<C> L(n), R(n), outs(n), outl(n);
	for(int i = 0; i < (int)a.size(); ++i) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
	for(int i = 0; i < (int)b.size(); ++i) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
	fft(L), fft(R);
	for(int i = 0; i < n; ++i) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	for(int i = 0; i < res.size(); ++i) {
		lint av = lint(real(outl[i])+.5), cv = lint(imag(outs[i])+.5);
		lint bv = lint(imag(outl[i])+.5) + lint(real(outs[i])+.5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}
