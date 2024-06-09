#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

mt19937 rng(time(0));

#include "../../content/number-theory/prime-counting.h"

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	ll N; cin >> N;
	primes_t P;
	cout << P.pi(N) << '\n';
}