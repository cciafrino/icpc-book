struct UnionFind{
  int n;
  vector<int> dad, rank;
  UnionFind(int n):n(n),dad(n),rank(n,0){
    iota(dad.begin(), dad.end(), 0);
  }
  int find(int v){return dad[v]==v?v:dad[v]=find(dad[v]);}
  int join(int a, int b){
    if(a=find(a) == b=find(b))return 0;
    if(rank[a]>rank[b])swap(a, b);
    dad[a]=b;
    if(rank[a]==rank[b])rank[b]++;
    return 1;
  }
};
