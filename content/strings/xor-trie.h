/**
 * Author: Chris
 * Source: bqi343
 * Description: Query get the maximum possible xor between an integer X and every possible 
 * subarray.
 * Just insert zero and for each prefix xor, insert it in the trie and query for max xor. 
 * The answer is the maximum possible value for each prefix query. 
 * Time: 
 * Status: tested in CSES1655 and DCPC2015E
 * Usage:
 */
template<int SZ, int MXBIT> struct Trie {
    int nxt[SZ][2], num = 0; // num is last node in trie
    unordered_map<int, int> nodes; 
    // change 2 to 26 for lowercase letters
    Trie() { memset(nxt,0,sizeof nxt); }
    void add(int x) { 
        int cur = 0;
        for(int i = MXBIT-1; i >= 0; --i) {
            int t = (x >> i) & 1;
            if (!nxt[cur][t]) nxt[cur][t] = ++num;
            cur = nxt[cur][t];
        }
        nodes[cur] = x; // leaf value
    }
    int query(int x) { 
        int cur = 0, ma = 0;
        for (int i = MXBIT-1; i >= 0; --i) {
            int t = ((x >> i) & 1) ^ 1;
            if (!nxt[cur][t]) t ^= 1;
            cur = nxt[cur][t];
            ma <<= 1; ma |= t;
        }
        // or return ma for max xor with one value instead of subarray
        return x ^ nodes[cur]; 
    }
};
