/**
 * Author:
 * Description: Counts 3 and 4 cycles
 * Time: O(E \sqrt E)
 * Status: Tested on library-checker and gcpc-2022F

 */
int count_cycles(const vector<vector<int>>& adj, const vector<int>& deg) {
	const int N = int(adj.size());
	vector<int> idx(N), loc(N);
	iota(idx.begin(), idx.end(), 0);
	sort(idx.begin(), idx.end(), [&](const int& a, const int& b) { return deg[a] < deg[b]; });
	for (int i = 0; i < N; ++i) loc[idx[i]] = i;

	vector<vector<int>> gr(N);
	for (int a = 0; a < N; ++a) {
		for (int b : adj[a]) {
			if (loc[a] < loc[b]) gr[a].push_back(b);
		}
	}
	
	int cycle3 = 0;
	{
		vector<bool> seen(N, false);
		for (int a = 0; a < N; ++a) {
			for (int b : gr[a]) seen[b] = true;
			for (int b : gr[a]) {
				for (int c : gr[b]) {
					if (seen[c]) {
						cycle3 += 1;
					}
				}
			}
			for (int b : gr[a]) seen[b] = false;
		}
	}
	int cycle4 = 0;
	{
		vector<int> cnt(N);
		for (int a = 0; a < N; ++a) {
			for (int b : adj[a]) {
				for (int c : gr[b]) {
					if (loc[a] < loc[c]) {
						cycle4 += 1;
						cnt[c]++;
					}
				}
			}
			for (int b : adj[a]) for (int c : gr[b]) cnt[c] = 0;
		}
	}

	return cycle3;
}
