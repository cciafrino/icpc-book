/**
 * Author: Simon Lindholm (adapted)
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected graph, and
 *  runs a callback for the edges in each. In a biconnected component there
 *  are at least two distinct paths between any two nodes. Note that a node can
 *  be in several components. An edge which is not in a component is a bridge,
 *  i.e., not part of any cycle.
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017
 * Usage:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) {
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); 
 *  }
 */

typedef vector<int> vi;
typedef vector<vector<pair<int,int>>> vii;

vector<int> num, st;
vii ed;
int Time;

int dfs(int at, int par,vector<vector<int>> &comps) {
	int me = num[at] = ++Time, e, y, top = me;
	for (auto &pa : ed[at]) if (pa.second != par) {
		tie(y, e) = pa;
		if (num[y]) {
			top = min(top, num[y]);
			if (num[y] < me) st.push_back(e);
		} else {
			int si = st.size();
			int up = dfs(y, e, comps);
			top = min(top, up);
			if (up == me) {
				st.push_back(e);
				comps.push_back(vector<int>());
				for(int i = st.size()-1;i >= si; --i)
					comps[comps.size()-1].push_back(st[i]);
				st.resize(si);
				cont_comp++;
			}
			else if (up < me){ st.push_back(e);}
			else { cont_comp++; comps.push_back({e});/* e is a bridge */ }
		}
	}
	return top;
}


vector<vector<int>> bicomps() { 
	// returns components and its edges ids
	vector<vector<int>> comps;
	num.assign(ed.size(), 0);
	for (int i = 0; i < ed.size(); ++i) 
		if (!num[i]) dfs(i, -1, comps);
	return comps;
}
