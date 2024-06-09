#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/number-theory/modular-arithmetic.h"

using num = modnum<998244353U>;

#include "../../content/numerical/root-of-unity-zp.h"
#include "../../content/numerical/fast-fourier-transform.h"

FFT<num> fft;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M;

	vector<num> A(N), B(M);
	for (auto& a : A) cin >> a.x;
	for (auto& b : B) cin >> b.x;

	auto C = fft.convolve(A, B);
	for (auto c : C) cout << c.x << ' ';
	cout << '\n';
}
