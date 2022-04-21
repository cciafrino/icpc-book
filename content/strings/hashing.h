/**
 * Author: Chris
 * Date: 2018-03-15
 * License: CC0
 * Source: own work
 * Description:
 * Status: not tested
 */
const int maxn = 400001;
const int mod = 1004669333, base = 33, inv_base = 121778101;
vector<int> base_pow(maxn + 1), inv_base_pow(maxn + 1);
void prep() { // 5c2398
    base_pow[0] = 1;
    for (int i = 1; i <= maxn; ++i)
        base_pow[i] = (lint)base_pow[i - 1] * base % mod;
    inv_base_pow[0] = 1;
    for (int i = 1; i <= maxn; ++i)
        inv_base_pow[i] = (lint)inv_base_pow[i - 1] * inv_base % mod;
}
struct hashes_t { // f1dd26
    string s;
    int n;
    vector<int> acc_hash, acc_inv_hash;
    hashes_t(const string &_s): s(_s), n(s.size()), acc_hash(n + 1, 0)
                            , acc_inv_hash(n + 1, 0) { // 127dd9
        for (int i = 0; i < n; ++i) {
            acc_hash[i + 1] = 
                (acc_hash[i] + (lint)base_pow[i] * (s[i] - 'a' + 1)) % mod;
            acc_inv_hash[i + 1] =
                (acc_inv_hash[i] + (lint)inv_base_pow[i] * (s[i] - 'a' + 1)) % mod;
        }
    }
    int get_hash(int a, int b) { // 04a73b
        assert(a <= b);
        int hash = acc_hash[b + 1] - acc_hash[a];
        if (hash < 0) hash += mod;
        hash = (lint)hash * inv_base_pow[a] % mod;
        return hash;
    }
    int get_inv_hash(int a, int b) { // d3dfd9
        assert(a <= b);
        int hash = acc_inv_hash[b + 1] - acc_inv_hash[a];
        if (hash < 0) hash += mod;
        hash = (lint)hash * base_pow[b] % mod;
        return hash;
    }
};
