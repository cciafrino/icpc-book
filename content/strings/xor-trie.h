/**
 * Author: Chris
 * Source: 
 * Description: Query get the maximum possible xor between an integer X and every possible 
 * subarray.
 * Just insert zero and for each prefix xor, insert it in the trie and query for max xor. 
 * The answer is the maximum possible value for each prefix query. 
 * Time: 
 * Status: tested in CSES1655 and DCPC2015E
 * Usage:
 */

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
