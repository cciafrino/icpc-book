#include<bits/stdc++.h>
using namespace std;

using lint = long long;

typedef long long H;
static const H M = INT_MAX;
static H C; // initialized below

// Arithmetic mod M. "typedef H K;" instead if you think
// test data is random. (Haha, good luck.)
struct K {
	H x; K(H x=0) : x(x) {}
	K operator+(K o) { H y = x + o.x; return y - (y >= M) * M; }
	K operator*(K o) { return x*o.x % M; }
	H operator-(K o) { H y = x - o.x; return y + (y < 0) * M; }
};

struct HashInterval {
	vector<K> ha, pw;
	HashInterval(string& str) : ha(str.size()+1), pw(ha) {
		pw[0] = 1;
		for(int i = 0; i < str.size(); ++i)
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

vector<H> getHashes(string& str, int length) {
	if (str.size() < length) return {};
	K h = 0, pw = 1;
	for(int i =0; i < length; ++i)
		h = h * C + str[i], pw = pw * C;
	vector<H> ret = {h - 0};
	ret.reserve(str.size() - length + 1);
	for(int i = length; i < str.size(); ++i) {
		ret.push_back(h * C + str[i] - pw * str[i-length]);
		h = ret.back();
	}
	return ret;
}

H hashString(string& s) {
	K h = 0;
	for (auto &c : s) h = h * C + c;
	return h - 0;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    string s, t;
    cin >> s >> t;
    HashInterval h(s), p(t);

    
    vector<H> ret = getHashes(s, 2);
    for (auto u : ret) cout << u << '\n';
    for (int i = 0; i < s.size(); ++i) cout << h.hashInterval(i, i+2) << '\n';
    
}