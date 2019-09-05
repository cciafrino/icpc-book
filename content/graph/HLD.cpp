//finish later!!

struct HL {
  using Edge = int;
  const std::vector<std::vector<Edge>>* graph;
  size_t n;
  std::vector<int> parent;
  std::vector<int> left;
  std::vector<int> right;
  std::vector<int> start;
  HL() {}
 
  static int vertex(const Edge& edge) {
    return edge;
  }
 
  void build(const std::vector<std::vector<Edge>>& graph);
 
  int dfsSize(int v, int prev, std::vector<int>& treeSize);
 
  int dfs(int v, int prev, const std::vector<int>& treeSize);
};
 
int HL::dfsSize(int v, int prev, std::vector<int>& treeSize) {
  int res = 1;
  for (const Edge& e : (*graph)[v]) {
    int nv = vertex(e);
    if (nv != prev) {
      res += dfsSize(nv, v, treeSize);
    }
  }
  treeSize[v] = res;
  return res;
}
 
int HL::dfs(int v, int prev, const std::vector<int>& treeSize) {
  parent[v] = prev;
  int maxV = -1;
  int maxSize = 0;
  for (const Edge& e : (*graph)[v]) {
    int nv = vertex(e);
    if (nv != prev) {
      if (treeSize[nv] > maxSize) {
        maxV = nv;
        maxSize = treeSize[nv];
      }
    }
  }
  int cur = left[v] + 1;
  if (maxV >= 0) {
    left[maxV] = cur;
    start[maxV] = start[v];
    cur = dfs(maxV, v, treeSize);
    for (const Edge& e : (*graph)[v]) {
      int nv = vertex(e);
      if (nv != prev && nv != maxV) {
        left[nv] = cur;
        start[nv] = nv;
        cur = dfs(nv, v, treeSize);
      }
    }
  }
  right[v] = cur;
  return cur;
}
 
void HL::build(const std::vector<std::vector<Edge>>& graph) {
  this->graph = &graph;
  n = graph.size();
  std::vector<int> treeSize(n);
  dfsSize(0, -1, treeSize);
  parent.resize(n);
  left.resize(n);
  right.resize(n);
  start.resize(n);
  dfs(0, -1, treeSize);
}
