/**
 * Author: Chris
 * Date: 2015-03-15
 * License: CC0
 * Source: BenQ + own work
 * Description: using pairs to reduce frequency of collision
 * Status: not tested
 */
#include<PairNumTemplate.h>
#include<ModTemplate.h>

using num = modnum<int(1e9)+7>;
using hsh = pairnum<num, num>;
const int MOD = int(1e9)+7;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> MULT_DIST(0.1 * MOD, 0.9 * MOD); 
hsh base(MULT_DIST(rng), MULT_DIST(rng));
hsh inv_base(1/base.t, 1/base.u);

struct hash_t {
    string s; 
    vector<hsh> base_pow, inv_base_pow, pref;
    hash_t(string &_s) : base_pow(_s.size()), inv_base_pow(_s.size()), 
	pref(s.size()+10) {
		s = _s;
		base_pow[0] = inv_base_pow[0] = 1;
		for (int i = 1; i < s.size(); ++i) {
			base_pow[i] = base_pow[i-1] * base;
			inv_base_pow[i] = inv_base_pow[i-1] * inv_base;
		}
		for (int i = 0; i < s.size(); ++i)
			pref[i+1] = pref[i] + base_pow[i] * (s[i] -'a' + 1);
	}
	hsh get_inv_hash(int a, int b) {
		assert(a <= b);
		return inv_base_pow[a] * (pref[b+1] - pref[a]);
	}
	hsh get_hash(int a, int b) {
		assert(a <= b);
		return pref[b] - pref[a] * base_pow[b - a];
	}
    int lcp(hash_t &b) {
        int left = 0, right = min(s.size(), (b.s).size());
        while (left < right) {
            int mid = (left + right + 1)/2;
            if (pref[mid] == b.pref[mid]) left = mid;
            else right = mid-1;
        }
        return left;
    }
};
