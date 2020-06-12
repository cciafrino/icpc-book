#include <bits/stdc++.h>
using namespace std;

#include "../../content/strings/AhoCorasick.h"

template<class F>
void gen(string& s, int at, int alpha, F f) {
	if (at == s.size()) f();
	else {
		for(int i = 0; i < alpha; ++i) {
			s[at] = (char)('A' + i);
			gen(s, at+1, alpha, f);
		}
	}
}

void test(const string& s) {
	vector<string> pats;
	string cur;
	for(int i = 0; i < s.size(); ++i) {
		if (s[i] == 'A') {
			pats.push_back(cur);
			cur = "";
		}
		else cur += s[i];
	}
	string hay = cur;
	for(string &x : pats) if (x.empty()) return;
	// Priority order of patterns for findAll: shorter patterns first, tie-broken by index
	vector<int> order(pats.size());
	iota(order.begin(), order.end(), 0);
	stable_sort(order.begin(), order.end(), [&](int a, int b) { 
		return pats[a].size() < pats[b].size(); 
	});
	AhoCorasick ac(pats);
	vector<vector<int>> positions = ac.findAll(pats, hay);
	vector<int> ord;
	for(int i = 0; i < hay.size(); ++i) {
		ord.clear();
		for(auto &j : order) {
			string& pat = pats[j];
			if (hay.substr(i, pat.size()) == pat) {
				ord.push_back(j);
			}
		}
		if (positions[i] != ord) {
			cerr << "failed!" << endl;
			cerr << hay << endl;
			for(auto &x : pats) cerr << x << endl;
			cerr << "failed at position " << i << endl;
			cerr << "got:" << endl;
			for(auto &x : positions[i]) cerr << x << ' ';
			cerr << endl;
			cerr << "expected:" << endl;
			for(auto &x : ord) cerr << x << ' ';
			cerr << endl;
			abort();
		}
	}
}

int main() {
	// test ~4^11 strings
	for(int n = 0; n < 12; ++n) {
		string s(n, 'x');
		gen(s, 0, 4, [&]() {
			test(s);
		});
	}
	// then ~5^8
	for(int n = 0; n < 9; ++n) {
		string s(n, 'x');
		gen(s, 0, 5, [&]() {
			test(s);
		});
	}
	cout<<"Tests passed!"<<endl;
}