/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: 
 * Description: Returns the number of msts in undirected weighted graph.
 * Status: somewhat tested - http://acm.hdu.edu.cn/showproblem.php?pid=4408
 * Time: 
 */
#include"dsumit.h"

lint det(vector<vector<lint>> a, int n, int p) {
	lint ans = 1;
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) a[i][j] %= p;
	for(int i = 1; i < n; ++i) {
		for(int j = i+1; j < n; ++j) {
			while (a[j][i] != 0) { // gcd step
				lint t = a[i][i] / a[j][i];
				if (t) for(int k = i; k < n; ++k) {
					a[i][k] = (a[i][k] - a[j][k] * t) % p;
					a[i][k] %= p;
				}
				swap(a[i], a[j]);
				ans *= -1;
			}
		}
		ans = ans * a[i][i] % p;
		if (!ans) return 0;
	}
	return (ans + p) % p;
}

struct edge_t {
	int u, v, w;
	bool operator<(const edge_t& o) const {
		return w < o.w;
	}
};

const int N = 101;
int edgenum = 0;
vector<edge_t> edge;
vector<bool> seen;
vector<int> g[N];
vector<vector<lint>> p, deg;

void addEdge(int u, int v, int d){
	edge_t E = { u, v, d };
	edge[++edgenum] = E;
}
 
lint MST_count(int n, lint MOD) {
	sort(edge.begin()+1, edge.begin()+edgenum+1);
	int pre = edge[1].w;
	lint ans = 1;
	UF a(n+1), b(n+1);
	seen = vector<bool>(n+1, false);
	deg = vector<vector<lint>>(n+1, vector<lint>(n+1));
	for (int i = 0; i <= n; i++) g[i].clear();
	for (int t = 1; t <= edgenum+1; ++t) {
		if (edge[t].w != pre || t == edgenum + 1) {
			for (int i = 1, k; i <= n; i++) if (seen[i]) {
				k = b.find(i);
				g[k].push_back(i);
				seen[i] = false;
			}
			for (int i = 1; i <= n; ++i)
				if (g[i].size()) {
					p = vector<vector<lint>>(n+1, vector<lint>(n+1));
					for (int j = 0; j < g[i].size(); j++)
					for (int k = j+1, x, y; k < g[i].size(); ++k) {
						x = g[i][j];
						y = g[i][k];
						p[j][k] = p[k][j] = -deg[x][y];
						p[j][j] += deg[x][y];
						p[k][k] += deg[x][y];
					}
					ans = ans*det(p, g[i].size(), MOD) % MOD;
					for (int j = 0; j < g[i].size(); ++j) a.par[g[i][j]] = i;
				}
			deg = vector<vector<lint>>(n+1, vector<lint>(n+1));
			for (int i = 1; i <= n; ++i) {
				b.par[i] = a.find(i);
				g[i].clear();
			}
			if (t == edgenum+1) break;
			pre = edge[t].w;
		}
		int x = a.find(edge[t].u);
		int y = a.find(edge[t].v);
		if (x == y) continue;
		seen[x] = seen[y] = true;
		b.unite(x, y);
		deg[x][y]++; deg[y][x]++;
	}
	if (!edgenum) return 0;
	for (int i = 2; i <= n; i++)
		if (b.find(i) != b.find(1))
			return 0;
	return ans;
}