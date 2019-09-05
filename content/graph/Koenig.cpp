/**
 * Author: Felipe Abella
 * Date: 
 * License: 
 * Source: folkore
 * Description: Given a bipartite graph $G$ find a vertex set $S \subseteq U \cup V$ of minimum size that cover all edges.
 */

struct BipartiteVertexCover { /// start-hash
  int nleft, nright;
  vector<bool> mark;
  Dinic din;
  BipartiteVertexCover(int nleft, int nright)
    : nleft(nleft), nright(nright), mark(1+nleft+nright+1)
    , din(1+nleft+nright+1, 0, 1+nleft+nright) {
    for (int l = 0; l < nleft; ++l) din.add_edge(0, 1+l, 1);
    for (int r = 0; r < nright; ++r) din.add_edge(1+nleft+r, 1+nleft+nright, 1);
  }
  void add_edge(int l, int r) {
    din.add_edge(1+l, 1+nleft+r, 1);
  }/// end-hash
  void dfs(int v) {/// start-hash
    mark[v] = true;
    for (int edid : din.adj[v]) {
      Dinic::edge &ed = din.edges[edid];
      if (ed.flow < ed.cap && !mark[ed.u])
	    dfs(ed.u);
    }
  }/// end-hash
  vector<pair<int, int>> solve() {/// start-hash
    int maxflow = din.maxflow();
    dfs(0);
    vector<pair<int, int>> result;
    for (int i = 0; i < (int)din.edges.size(); ++i) {
      Dinic::edge &ed = din.edges[i];
      int to = ed.u, from = din.edges[i^1].u;
      if (mark[from] && !mark[to] && ed.cap > 0) {
	    if (from == 0) result.push_back({0, to-1});
	    else result.push_back({1, from-1-nleft});
      }
    }
    assert(maxflow == result.size());
    return result;
  }/// end-hash
};
