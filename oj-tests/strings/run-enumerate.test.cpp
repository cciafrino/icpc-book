#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate"
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

mt19937 rng(time(0));

#include "../../content/strings/suffix-array.h"
#include "../../content/strings/tandem-repeats.h"

int main() {
	using namespace std;
	cin.tie(nullptr)->sync_with_stdio(false);
	string S; cin >> S;

	auto tr = run(int(S.size()), S);

	for (auto& t : tr) {
		t = {t[2], t[0], t[1] + 2*t[2]};
	}

	sort(tr.begin(), tr.end());

	vector<array<int, 3>> ans;
	set<pair<int, int>> tab;
	for (auto t : tr) {
		if (tab.count({t[1], t[2]}) > 0) continue;
		tab.insert({t[1], t[2]});
		ans.push_back(t);
	}

	cout << int(ans.size()) << '\n';
	for (auto [x, y, z] : ans) {
		cout << x << ' ' << y << ' ' << z << '\n';
	}
}
