struct SCC {
    int n;
    vector<vector<int>> graph;
    vector<int> vis, reach; // st is time you reach, scc is min t reachable
    vector<int> stk;
    vector<int> scc;
    vector<vector<int>> scclist;
    int t, cnt;
    SCC(int n = 0) : n(n), graph(n), vis(n), reach(n), scc(n), t(0) {}
    void dfs(int a){
        stk.push_back(a);
        vis[a] = reach[a] = t;
        t++;
        for(int u : graph[a]){
            if(scc[u] != -1) continue;
            if(vis[u] == 0) dfs(u);
            reach[a] = min(reach[a], reach[u]);
        }
        if(vis[a] == reach[a]){
            while(1){
                int l = stk[stk.size()-1];
                scc[l] = cnt;
                stk.pop_back();
                if(l == a) break;
            }
            cnt++;
        }
    }
    void findscc(){
        t = 1; cnt = 0;
        stk.clear();
        for(int i = 0; i < n; i++){
            vis[i] = reach[i] = 0;
            scc[i] = -1;
        }
        for(int i = 0; i < n; i++) if(vis[i] == 0) dfs(i);
        scclist.clear();
        scclist.resize(cnt);
        for(int i = 0; i < n; i++) scclist[scc[i]].push_back(i);
    }
};
