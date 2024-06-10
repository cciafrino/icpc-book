#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

mt19937 rng(time(0));

#include "../../content/strings/suffix-array.h"

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	string S; cin >> S;

	suffix_array_t us(S.begin(), S.end());
	for (int i = 1; i < int(us.sa.size()); ++i) {
		cout << us.sa[i] << "\n "[i+1 < int(us.sa.size())];
	}
}
