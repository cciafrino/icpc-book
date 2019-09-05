/**
 * Author: Lukas Polacek (Modificado por: Chris)
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 * Usage: scc(graph, [\&](vi\& v) { ... }) visits all
 * components in reverse topological order. comp[i] holds the
 * component index of a node (a component only has edges to
 * components with lower index). ncomps will contain the
 * number of components.
 */
#pragma once

vector<int> val, comp, z, cont;
int time, ncomps;
template<class G, class F> int dfs(int v, G &g, F f) {
	int reach = val[v] = ++time, u; 
	z.push_back(v);
	for(auto &e : g[v]) if (comp[e] == -1)
		reach = min(reach, val[e] ?: dfs(e,g,f));
	if (reach == val[v]) {
		do {
			u = z.back(); z.pop_back();
			comp[u] = ncomps;
			cont.push_back(u);
		} while (u != v);
		f(cont); 
		cont.clear();
		ncomps++;
	}
	return val[v] = reach;
}
template<class G, class F> void tarjan(G &g, F f) {
	int n = g.size();
	val.assign(n, 0); comp.assign(n, -1);
	time = ncomps = 0;
        for(int i = 0; i < n; ++i) if (comp[i] == -1) dfs(i, g, f);
}
