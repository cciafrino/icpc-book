#define PROBLEM "https://judge.yosupo.jp/problem/product_of_polynomial_sequence"
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
	int N; cin >> N;

	if (N == 0) {
		cout << 1 << '\n';
		exit(0);
	}
	vector<vector<num>> poly(N);
	
	for (int i = 0; i < N; ++i) {
		int d; cin >> d;
		poly[i].resize(d+1);
		for (int j = 0; j <= d; ++j) {
			cin >> poly[i][j].x;
		}
	}

	auto rec = [&](auto&& self, int l, int r) -> vector<num> {
		if (r - l == 1) return poly[l];
		int md = (l + r) / 2;
		return fft.convolve(self(self, l, md), self(self, md, r));
	};

	auto ans = rec(rec, 0, N);
	for (auto v : ans) {
		cout << v.x << ' ';
	}
	cout << '\n';
}
