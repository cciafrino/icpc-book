/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected graph, and
 *  runs a callback for the edges in each. In a biconnected component there
 *  are at least two distinct paths between any two nodes. Note that a node can
 *  be in several components. An edge which is not in a component is a bridge,
 *  i.e., not part of any cycle.
 *  $make_bcc_tree$ constructs the block cut tree of given graph. The first
 *  $comps.size()$ nodes represents the blocks, the others represents the
 *  cut vertices.
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017, make_bcc_tree is not well tested
 * Usage:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) {
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); }
 *  bicomps([\&](const vi\& edgelist) {...});
 */
vector<int> num, st, stk;
vector<vector<int>> two_edge_cc; // two-edge-connected components
vector<vector<pii>> ed;
int Time;
template<class F> int dfs(int at, int par, F& f) {
	int me = num[at] = ++Time, e, y, top = me;
	stk.push_back(at);
	for(auto &pa : ed[at]) if (pa.second != par) {
		tie(y, e) = pa;
		if (num[y]) {
			top = min(top, num[y]);
			if (num[y] < me) st.push_back(e);
		} else {
			int si = int(st.size());
			int up = dfs(y, e, f);
			top = min(top, up);
			if (up == me) {
				st.push_back(e);
				f(vector<int>(st.begin() + si, st.end()));
				st.resize(si);
			}
			else if (up < me) st.push_back(e);
			else { /* e is a bridge */ }
		}
	}
	if (top >= num[at]) {
		vector<int> cur_two_edge_cc;
		while (stk.back() != at) {
			cur_two_edge_cc.push_back(stk.back());
			stk.pop_back();
		}
		cur_two_edge_cc.push_back(stk.back());
		stk.pop_back();
		two_edge_cc.push_back(cur_two_edge_cc);
	}
	return top;
}

template<class F> void bicomps(F f) {
	Time = 0;
	st.resize(0);
	num.assign(ed.size(), 0);
	for(int i = 0; i < int(ed.size()); ++i) 
		if (!num[i]) dfs(i, -1, f);
}

using vvi = vector<vector<int>>;
tuple<vvi, vvi, vector<int>> make_bcc_tree(const G &ed, const vector<pair<int,int>> &edges){
	int nart = 0, ncomp = 0, n = int(ed.size());
	vector<int> inv(n);
	vvi comps;
	bicomps(ed, [&](const vector<int> &eid){
		ncomp++;
		set<int> cur;
		for(int e: eid){			
			cur.insert(edges[e].first);
			cur.insert(edges[e].second);	
		}
		comps.push_back(vector<int>(cur.begin(), cur.end()));
		for(int v: cur) inv[v]++;
	} );
	vector<int> art;
	for(int u = 0; u < n; u++)
		if(inv[u] > 1){
			inv[u] = nart++;
			art.push_back(u);
		} else inv[u] = -1;
	vvi tree(ncomp + nart);
	for(int c = 0; c < ncomp; c++)
		for(int u: comps[c])
			if(inv[u] != -1){
				tree[ c ].push_back( ncomp + inv[u] );
				tree[ ncomp + inv[u] ].push_back( c );
			}
	return {tree, comps, art};
}
