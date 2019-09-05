/**
 * Author: Chris
* Description: Eulerian undirected/directed path/cycle algorithm. Returns a list of nodes in the Eulerian path/cycle with src at both start and end, or
 *  empty list if no cycle/path exists. To get edge indices back, also put it->second in s (and then ret).
 * Time: O(E) where E is the number of edges.
 * Status: tested
 */

struct edge {
    vector<pair<int,int>> outs; // (dest, edge index)
    int nins = 0;
};

vector<int> euler_walk(vector<edge> &nodes, int nedge, int src=0) { /// start-hash
	int c = 0;
	for (auto &n : nodes) c += abs(n.nins - n.outs.size());
	if (c > 2) return {};
	vector<vector<pii>::iterator> its;
	for (auto &n : nodes) its.push_back(n.outs.begin());
	vector<bool> eu(nedge);
	vector<int> ret, s = {src};
	while(!s.empty()) {
		int x = s.back();
		auto &it = its[x], end = nodes[x].outs.end();
		while(it != end && eu[it->second]) ++it;
		if(it == end) { ret.push_back(x); s.pop_back(); }
		else { s.push_back(it->first); eu[it->second] = true; }
	}
	if(ret.size() != nedge+1)
		ret.clear(); // No Eulerian cycles/paths.
	// else, non-cycle if ret.front() != ret.back()
	reverse(ret.begin(), ret.end());
	return ret;
}/// end-hash
