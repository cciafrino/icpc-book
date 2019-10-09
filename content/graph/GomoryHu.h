/**
 * Author: BenQ
 * Date: 2019-04-26
 * License: CC0
 * Source: 
 * Description: 
 * Status: Not tested
 */

struct GomoryHu {
	int n;
	vector<pair<pair<int,int>, int> edges;
	vector<vector<int>> color = {{}};
	vector<map<int,int>> adj;
	vector<int> side;
	GomoryHu(int _n) : n(_n), adj(2*n), side(n) {}
	void addEdges(int a, int b, int c) { edges.push_back({{a,b},c}); }
	int solve(vector<vector<int>> &cc) {
		Dinic dinitz;
		vector<int> stuff(n+1);
		for (int i = 0; i < cc.size(); ++i)
			for (int u : cc[i]) stuff[u] = i;
		for (int u : edges)
			if (stuff[u.first.first] != stuff[u.first.second]) {
				dinitz.addEdge(stuff[u.first.first], stuff[u.first.second], u.second);
				dinitz.addEdge(stuff[u.first.second], stuff[u.first.first], u.second);
			}
		int flow = dinitz.maxflow(0, 1);
		for (int i = 0; i < cc.size(); ++i)
			for (int u : cc[i]) side[u] = dinitz.lvl[i] >= 0; //min-cut
		return flow;
	}
	void fill(vector<int> &v, int a, int b) {
		for (int u : color[a]) v.push_back(u);
		for (int u : adj[a]) if (u.first != b) fill(v, u.first, a);
	}
	void addTree(int a, int b, int c) { adj[a][b] = c, adj[b][a] = c; }
	void deleteTree(int a, int b, int c) { adj[a].erase(b), adj[b].erase(a); }
	vector<pair<pair<int,int>,int>> make_tree(int N) {
		n = N;
		for (int i = 1; i <= n; ++i) color[0].push_back(i);
		vector<int> todo; 
		todo.push_back(0);
		while(!todo.empty()) {
			int x = todo.front();
			todo.pop_front();
			vector<vector<int>> cc;
			for (int u : color[x]) cc.push_back({u});
			for (int u : adj[x]) {
				cc.push_back({});
				fill(cc.back(), t.first, x);
			}
			int flow = solve(cc);
			color.push_back({});
			color.push_back({});
			for (int u : color[x]) color[color.size() - 2 + side[u]].push_back(u);
			for (int i = 0; i < 2; ++i)
				if (color[color.size()-2+i].size() > 1) todo.push_back(color.size()-2+i);
			for (int i = 0; i < color.size()-2; ++i)
				if (i != x && adj[i].count(x)) {
					addTree(i, color.size()-2+side[color[i][0]], adj[i][x]);
					deleteTree(i, x);
				} // modify tree edges
				addTree(color.size()-2, color.size()-1, flow);
		}
		vector<pair<pair<int,int>,int>> result;
		for (int i = 0; i < color.size(); ++i)
			for (int u : adj[i]) if (i < u.first) 
				result.push_back({{color[i][0], color[u.first][0]}, u.second});
		return result;
	}
};