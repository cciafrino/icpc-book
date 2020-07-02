/**
 * Author: BenQ
 * Source: 
 * Description: Query max xor with some int in the xor trie
 * Time: 
 * Status: Fuzz-tested
 * Usage:
 */
 
template<int MX, int MXBIT> 
struct xorTrie {
    int nxt[MX][2], sz[MX];// num is last node in trie
    int num = 0;
    // change 2 to 26 for lowercase letters
    xorTrie() { memset(nxt, 0, sizeof nxt), memset(sz, 0, sizeof sz); }
    // add or delete
    void add(lint x, int a = 1) { 
        int cur = 0; sz[cur] += a; 
        for(int i = MXBIT-1; i >= 0; --i) {
            int t = (x & (1 << i)) >> i;
            if (!nxt[cur][t]) nxt[cur][t] = ++num;
            sz[cur = nxt[cur][t]] += a;
        }
    }
    // compute max xor
    lint query(lint x) {
        if (sz[0] == 0) return INT_MIN; // no elements in trie
        int cur = 0;
        for(int i = MXBIT-1; i >= 0; --i) {
            int t = ((x & (1 << i)) >> i) ^ 1;
            if (!nxt[cur][t] || !sz[nxt[cur][t]]) t ^= 1;
            cur = nxt[cur][t]; if (t) x ^= 1lint<<i;
        }
        return x;
    }
};
