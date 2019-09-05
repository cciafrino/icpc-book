#define st first
#define nd second

vector<int> dijkstra(int s){
  vector<int> dis(n, inf);
  set<pair<int, int> > alvo;
  dis[s]=0;
  for(auto v:adj[s])alvo.insert({v.nd, v.st});
  while(!alvo.empty()){
    auto u=*alvo.begin();
    alvo.erase(alvo.begin());
    if(dis[u.nd]!=inf)continue;
    dis[u.nd]=u.st;
    for(auto v:adj[u.nd])
      if(dis[v.st]==inf)
        alvo.insert({dis[u.nd]+v.nd, v.st});
  }
  return dis;
}
