/**
 * Author: BenQ
 * Source: 
 * Description: Query max xor with some int in the Trie
 * Time: 
 * Status: Fuzz-tested
 * Usage:
 */
 
template<int MX, int MXBIT> struct Trie { /// start-hash
    vector<vector<int>> nex;// num is last node in trie
    vector<int> sz;
    int num = 0;
    // change 2 to 26 for lowercase letters
    Trie() {
        nex = vector<vector<int>>(MX, vector<int>(2));
        sz = vector<int>(MX);
    } /// end-hash
    // insert or delete
    void insert(lint x, int a = 1) { /// start-hash
        int cur = 0; sz[cur] += a; 
        for(int i = MXBIT-1; i >= 0; --i) {
            int t = (x&(1lint<<i))>>i;
            if (!nex[cur][t]) nex[cur][t] = ++num;
            sz[cur = nex[cur][t]] += a;
        }
    }/// end-hash
    // compute max xor
    lint test(lint x) {  /// start-hash
        if (sz[0] == 0) return -INF; // no elements in trie
        int cur = 0;
        for(int i = MXBIT-1; i >= 0; --i) {
            int t = ((x&(1lint<<i))>>i) ^ 1;
            if (!nex[cur][t] || !sz[nex[cur][t]]) t ^= 1;
            cur = nex[cur][t]; if (t) x ^= 1lint<<i;
        }
        return x;
    }/// end-hash
};
