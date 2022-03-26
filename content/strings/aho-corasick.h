/**
 * Author: Chris
 * Source: 
 * Description:
 * Status: tested
 */
vector<int> bfs; bfs.reserve(trie.size());
vector<int> failure(trie.size());
failure[0] = -1;
top_failure[0] = -1;
bfs.push_back(0);

for (int z = 0; z < int(bfs.size()); ++z) {
    int cur = bfs[z];
    if (z) top_failure[cur] = is_end[failure[cur]] ? failure[cur] : top_failure[failure[cur]];
    for (int c = 0; c < 26; ++c) {
        if (trie[cur][c] == -1) {
            trie[cur][c] = z ? trie[failure[cur]][c] : 0;
        } else {
            failure[trie[cur][c]] = z ? trie[failure[cur]][c] : 0;
            bfs.push_back(trie[cur][c]);
        }
    }
}
