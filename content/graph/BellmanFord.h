/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest paths from $s$ in a graph that might have negative edge weights.
 * Unreachable nodes get dist = inf; nodes reachable through negative-weight cycles get dist = -inf.
 * Assumes $V^2 \max |w_i| < \tilde{} 2^{63}$.
 * Time: O(VE)
 * Status: Tested on kattis:shortestpath3
 */
const lint inf = LLONG_MAX;
struct edge_t { int a, b, w, s() { return a < b ? a : -a; }};
struct node_t { lint dist = inf; int prev = -1; };
void bellmanFord(vector<node_t>& nodes, vector<edge_t>& eds, int s) {
	nodes[s].dist = 0;
	sort(eds.begin(), eds.end(), [](edge_t a, edge_t b) { return a.s() < b.s(); });
	int lim = nodes.size() / 2 + 2; // /3+100 with shuffled vertices
	for(int i = 0; i < lim; ++i) for(auto &ed : eds) {
		node_t cur = nodes[ed.a], &dest = nodes[ed.b];
		if (abs(cur.dist) == inf) continue;
		lint d = cur.dist + ed.w;
		if (d < dest.dist) {
			dest.prev = ed.a;
			dest.dist = (i < lim-1 ? d : -inf);
		}
	}
	for(int i = 0; i < lim; ++i) for(auto &e : eds) 
		if (nodes[e.a].dist == -inf) nodes[e.b].dist = -inf;
}
