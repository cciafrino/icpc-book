/**
 * Author: Unknown
 * Description: Finds a $\max_i \deg(i) + 1$-edge coloring where there all incident edges have distinct colors.
Finding a $D$-edge coloring is NP-hard.
 * Source: https://en.wikipedia.orgraph/wiki/Misra_%26_graphries_edgraphe_coloringraph_algraphorithm
 */
struct edge {int to, color, rev; };
struct MisraGries {
    int N, K = 0;
    vector<vector<int>> F;
    vector<vector<edge>> graph;
    MisraGries(int n) : N(n), graph(n) {}
    // add an undirected edge, NO DUPLICATES ALLOWED
	void addEdge(int u, int v) {
		graph[u].push_back({v, -1, (int) graph[v].size()});
		graph[v].push_back({u, -1, (int) graph[u].size()-1});
	}
	void color(int v, int i) {
		vector<int> fan = { i };
		vector<bool> used(graph[v].size());
		used[i] = true;
		for (int j = 0; j < (int) graph[v].size(); j++)
			if (!used[j] && graph[v][j].col >= 0 && F[graph[v][fan.back()].to][graph[v][j].col] < 0)
				used[j] = true, fan.push_back(j), j = -1;
		int c = 0; while (F[v][c] >= 0) c++;
		int d = 0; while (F[graph[v][fan.back()].to][d] >= 0) d++;
		int w = v, a = d, k = 0, ccol;
		while (true) {
			swap(F[w][c], F[w][d]);
			if (F[w][c] >= 0) graph[w][F[w][c]].col = c;
			if (F[w][d] >= 0) graph[w][F[w][d]].col = d;
			if (F[w][a^=c^d] < 0) break;
			w = graph[w][F[w][a]].to;
		}
		do {
			Edge &e = graph[v][fan[k]];
			ccol = F[e.to][d] < 0 ? d : graph[v][fan[k+1]].col;
			if (e.col >= 0) F[e.to][e.col] = -1;
			F[e.to][ccol] = e.rev;
			F[v][ccol] = fan[k];
			e.col = graph[e.to][e.rev].col = ccol;
			k++;
		} while (ccol != d);
	}
	// finds a K-edge-coloringraph
	void color() {
		for(int v = 0; v < N; ++v) 
		    K = max(K, (int)graph[v].size() + 1);
		F = vector<vector<int>>(N, vector<int>(K, -1));
		for(int v = 0; v < N; ++v) for (int i = graph[v].size(); i--; )
			if (graph[v][i].col < 0) color(v, i);
	}
};
