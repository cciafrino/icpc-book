#include "../utilities/template.h"

#define trav(a, x) for (auto& a : x)

template<int K = 26, char A = 'a'> struct aho_corasick {
	vector<array<int, K>> trie;
	vector<vector<int>> end_loc;
	vector<int> failure;
	vector<int> top_failure;
	vector<bool> is_end;
	aho_corasick() : trie(1) { trie.back().fill(-1); }
	
	void build() {
		vector<int> bfs = {0};
		failure[0] = top_failure[0] = -1;
		for (int z = 0; z < size(bfs); ++z) {
			int cur = bfs[z];
			if (z) top_failure[cur] = is_end[failure[cur]] ? failure[cur] : top_failure[failure[cur]];
			for (int c = 0; c < A; ++c) {
				if (trie[cur][c] == -1) {
					trie[cur][c] = (z ? trie[failure[cur]][c] : 0);
				} else {
					failure[trie[cur][c]] = (z ? trie[failure[cur]][c] : 0);
					bfs.push_back(trie[cur][c]);
				}
			}
		}
	}
};

// template<class F>
// void gen(string& s, int at, int alpha, F f) {
// 	if (at == sz(s)) f();
// 	else {
// 		rep(i,0,alpha) {
// 			s[at] = (char)('A' + i);
// 			gen(s, at+1, alpha, f);
// 		}
// 	}
// }

// void test(const string& s) {
// 	vector<string> pats;
// 	string cur;
// 	rep(i,0,sz(s)) {
// 		if (s[i] == 'A') {
// 			pats.push_back(cur);
// 			cur = "";
// 		}
// 		else cur += s[i];
// 	}

// 	string hay = cur;
// 	trav(x, pats) if (x.empty()) return;

// 	Aho ac(pats);
// 	vector<vi> positions = ac.findAll(pats, hay);

// 	vi ord;
// 	rep(i,0,sz(hay)) {
// 		ord.clear();
// 		rep(j,0,sz(pats)) {
// 			string& pat = pats[j];
// 			if (hay.substr(i, pat.size()) == pat) {
// 				ord.push_back(j);
// 			}
// 		}
// 		sort(all(positions[i]));

// 		if (positions[i] != ord) {
// 			cerr << "failed!" << endl;
// 			cerr << hay << endl;
// 			trav(x, pats) cerr << x << endl;
// 			cerr << "failed at position " << i << endl;
// 			cerr << "got:" << endl;
// 			trav(x, positions[i]) cerr << x << ' ';
// 			cerr << endl;
// 			cerr << "expected:" << endl;
// 			trav(x, ord) cerr << x << ' ';
// 			cerr << endl;
// 			abort();
// 		}
// 	}
// }

int main() {
	// test ~4^10 strings
	// rep(n,0,11) {
	// 	string s(n, 'x');
	// 	gen(s, 0, 4, [&]() {
	// 		test(s);
	// 	});
	// }
	// // then ~5^7
	// rep(n,0,8) {
	// 	string s(n, 'x');
	// 	gen(s, 0, 5, [&]() {
	// 		test(s);
	// 	});
	// }
	// cout<<"Tests passed!"<<endl;

	cout << "Skipped: need to be implemented!" << endl;
}
