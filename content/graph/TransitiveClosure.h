/**
 * Author: Chris
 * Date: 2019
 * License: CC0
 * Source: Wikipedia
 * Description: Given a directed graph adjacency matrix, computes closure, 
 * where $closure[i][j] = 1$ if there is a path from $i$ to $j$
 * in the graph. Closure is computed in $O(N^3 / 64)$ due to bitset.
 * Also supports adding an edge to the graph and updating the closure accordingly in $O(N^2 / 64)$.
 * Time: $O(N^3/64)$
 * Status: Not tested
 */

template<int sz>
struct TC {
	vector<bitset<sz>> closure;
	TC(vector<vector<int>> adj) : closure(sz) {
		for(int i = 0; i < sz; ++i)
			for(int j = 0; j < sz; ++j)
				closure[i][j] = adj[i][j];
		for(int i = 0; i < sz; ++i)
			for(int j = 0; j < sz; ++j)
				if (closure[j][i])
					closure[j] |= closure[i];
	}
	void addEdge(int a, int b) {
		if (closure[a][b]) return;
		closure[a].set(b);
		closure[a] |= closure[b];
		for (int i = 0; i < sz; ++i)
			if (closure[i][a]) closure[i] |= closure[a];
	}
};