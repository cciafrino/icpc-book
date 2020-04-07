/**
 * Author: Chris
 * Date: 
 * License:
 * Source: own work
 * Description: Simple, short and efficient hashing using pairs to reduce load factor.
 * Status: not tested
 */
#include<ModTemplate.h>
#include<PairNumTemplate.h>
using num = modnum<int(1e9)+7>;
using hsh = pairnum<num, num>;
const hsh BASE(163, 311);
// uniform_int_distribution<int> MULT_DIST(0.1*MOD,0.9*MOD); 
// constexpr hsh BASE(MULT_DIST(rng), MULT_DIST(rng));
struct hash_t {
    int n;
    string str;
    vector<hsh> hash, basePow;
    hash_t(const string& s) : n(s.size()), str(s), hash(n+1), basePow(n) {
        basePow[0] = 1;
        for (int i = 1; i < n; ++i) basePow[i] = basePow[i-1] * BASE;
        for (int i = 0; i < n; ++i) 
            hash[i+1] = hash[i] * BASE + hsh(s[i]);
    }
    hsh get_hash(int left, int right) {
        assert(left <= right);
        return hash[right] - hash[left] * basePow[right - left];
    }
    int lcp(hash_t &other) { // need some testing
        int left = 0, right = min(str.size(), other.str.size());
        while (left < right) {
            int mid = (left + right + 1)/2;
            if (hash[mid] == other.hash[mid]) left = mid;
            else right = mid-1;
        }
        return left;
    }
};
vector<int> rabinkarp(string t, string p) {
    vector<int> matches;
    hsh h(0, 0);
    for (int i = 0; i < p.size(); ++i) 
        h = BASE * h + hsh(p[i]);
    hash_t result(t);
    for (int i = 0; i + p.size() <= t.size(); ++i)
        if (result.get_hash(i, i + p.size()) == h)
            matches.push_back(i);
    return matches;
}