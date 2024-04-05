#include "../utilities/template.h"

#include "../../content/strings/rolling-hash.h"

typedef uint64_t ull;
#include"../utilities/random.h"
#include <sys/time.h>

bool is_nice(H x) {
	if (gcd(x.get(), UINT64_MAX) != 1) return false;
	H cur = x;
	for (ll i = 0; i < ll(1e9); i++) {
		if (cur.get() < ll(1e9)) return false;
		cur = cur * x;
	}
	return true;
}

void deterministic() {
	assert(is_nice(C));
}

void fuzz() {
	rep(times, 0, 10000) {
		int n = randIncl(1, 1000);
		string t, s;
		for (int i = 0; i < n; ++i) {
			s.push_back(char('a' + randIncl(0, 25)));
		}
		do {
			t.clear();
			for (int i = 0; i < n; ++i) {
				t.push_back(char('a' + randIncl(0, 25)));
			}
		} while (s == t);
		string input = s+t+s;
		HashInterval H(input);
		assert(H(0, n).get() != H(n, n*2).get());
		assert(H(0, n).get() == H(n*2, n*3).get());
	}
}

int main() {
	assert((H(1)*2+1-3).get() == 0);

	rep(it,0,10000) {
		int n = rand() % 10;
		int alpha = rand() % 10 + 1;
		string s;
		rep(i,0,n) s += (char)('a' + rand() % alpha);
		HashInterval hi(s);
		set<string> strs;
		set<ull> hashes;

		// HashInterval
		rep(i,0,n+1) rep(j,i,n+1) {
			string sub = s.substr(i, j - i);
			ull hash = hash_all(sub).get();
			assert(hi(i, j).get() == hash);
			hashes.insert(hash);
			strs.insert(sub);
		}

		// getHashes
		rep(le,1,n+1) {
			auto ve = get_hashes(s, le);
			assert(sz(ve) == n-le+1);
			rep(i,0,n-le+1) {
				assert(ve[i].get() == hi(i, i + le).get());
			}
		}

		// No collisions
		assert(sz(strs) == sz(hashes));
	}

	deterministic();
	fuzz();
	cout<<"Tests passed!"<<endl;
}
