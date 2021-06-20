#include<bits/stdc++.h>
using namespace std;

template<int K = 31> struct trie_t {
    vector<array<int, 2>> trie;
    trie_t() : trie(1, {-1, -1}) {}
    void add(int val) {
        int cur = 0;
        for (int a = K; a >= 0; --a) {
            int b = (val >> a) & 1;
            if (trie[cur][b] == -1) {
                trie[cur][b] = size(trie);
                trie.push_back({-1, -1});
            }
            cur = trie[cur][b];
        }
    }
    int max_xor(int val) {
        int cur = 0, mask = 0;
        for (int a = K; a >= 0; --a) {
            int b = (val >> a) & 1;
            if (trie[cur][!b] == -1) {
                cur = trie[cur][b];
            } else {
                mask |= (1 << a);
                cur = trie[cur][!b];
            }
        }
        return mask;
    }
};

template<typename T> inline void setmax(T& a, const T& b) { if (b > a) a = b; }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit | cin.eofbit | cin.badbit);
    int N; cin >> N;

    vector<int> A(N);
    for (int& a : A) cin >> a;

    trie_t tree;
    tree.add(0);

    int prefix_xor = 0;
    int max_xor = 0;
    for (int i = 0; i < N; ++i) {
        prefix_xor ^= A[i];
        tree.add(prefix_xor);
        setmax(max_xor, tree.max_xor(prefix_xor));
    }

    cout << max_xor << '\n';
}
