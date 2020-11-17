/**
 * Author: Chris
 * License: 
 * Description: 
 * Source: brunomont
 * Time: O(n)
 * Status: untested
 */
#include<KMP.h>
const int N = 5050;
int nxt[N][26];

void build(const string& S) {
	auto P = pi(S);
	nxt[0][S[0] - 'a'] = 1;
	for (int i = 1; i <= int(S.size()); ++i)
		for (char c = 0; c < 26; ++c) 
			nxt[i][c] = (c == S[i] - 'a' ? i + 1 : nxt[P[i - 1][c]]);
}

vector<int> match(string& T, string& P) {
	build(P);
	vector<int> match;
	int cur = 0;
	for (int i = 0; i < int(T.size()); ++i) {
		cur = nxt[T[i] - 'a'][cur];
		if (cur == int(P.size())) 
			match.push_back(i - cur + 1);
	}
	return match;
}
