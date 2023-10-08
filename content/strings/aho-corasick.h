/**
 * Author: Chen
 * Source: 
 * Description:
 * Status: tested
 */
const int sigma = 26;
array<int, sigma> init;
for (int i = 0; i < sigma; i++) init[i] = -1;
vector<array<int, sigma>> trie(1, init);
vector<int> out(1, -1), parent(n, -1), ids(n);
for (int i = 0; i < n; i++) {
	int cur = 0;
	for (char ch : s[i]) {
		int c = ch - 'a';
		if (trie[cur][c] == -1) {
			trie[cur][c] = (int)trie.size();
			trie.push_back(init); out.push_back(-1);
		}
		cur = trie[cur][c];
	}
	if (out[cur] == -1) out[cur] = i;
	ids[i] = out[cur];
}
vector<int> bfs,f(trie.size()); bfs.reserve(trie.size());
for (int c = 0; c < sigma; c++)
	if (trie[0][c] == -1) trie[0][c] = 0;
	else bfs.push_back(trie[0][c]);
for (int z = 0; z < (int)bfs.size() ; z++) {
	int cur = bfs[z];
	for (int c = 0; c < sigma; c++) {
		if (trie[cur][c] == -1)
			trie[cur][c] = trie[f[cur]][c];
		else {
			int nxt = trie[cur][c];
			int fail = trie[f[cur]][c];
			if (out[nxt] == -1) out[nxt] = out[fail];
			else parent[out[nxt]] = out[fail];
			f[nxt] = fail; bfs.push_back(nxt);
		}
	}
}
