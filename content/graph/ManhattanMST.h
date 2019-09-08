/**
 * Author: BenQ
 * Description: Compute MST of points where edges are manhattan distances
 * Status: Tested on kattis gridmst
 */
#include<UnionFind.h>
#include<Kruskal.h>

int N;
vector<array<int,3>> cur;
vector<pair<lint,pair<int, int>>> ed;
vector<int> ind;

struct {
    map<int,pair<int, int>> m;
    void upd(int a, pair<int, int> b) { 
        auto it = m.lower_bound(a);
        if (it != m.end() && it->second <= b) return;
        m[a] = b; it = m.find(a);
        while (it != m.begin() && prev(it)->second >= b) m.erase(prev(it));
    }
    
    pair<int, int> query(int y) { // for all a > y find min possible value of b 
        auto it = m.upper_bound(y);
        if (it == m.end()) return {2*MOD,2*MOD};
        return it->second;
    }
} S;

void solve() {
    sort(ind.begin(), ind.end(), [](int a, int b) { return cur[a][0] > cur[b][0]; });
    S.m.clear();
    int nex = 0;
    for(auto &x : ind) { // cur[x][0] <= ?, cur[x][1] < ? 
        while (nex < N && cur[ind[nex]][0] >= cur[x][0]) {
            int b = ind[nex++]; 
            S.upd(cur[b][1],{cur[b][2],b});
        }
        pair<int, int> t = S.query(cur[x][1]);
        if (t.second != 2*MOD) ed.push_back({(lint)t.first-cur[x][2],{x,t.second}});
    }
}

lint mst(vector<pair<int, int>> v) {
    N = v.size(); cur.resize(N); ed.clear(); 
    ind.clear(); for(int i = 0; i < N; ++i) ind.push_back(i);
    sort(ind.begin(), ind.end(), [&v](int a, int b) { return v[a] < v[b]; });
    for(int i = 0; i < N-1; ++i) if (v[ind[i]] == v[ind[i+1]]) ed.push_back({0,{ind[i],ind[i+1]}});
    
    for(int i = 0; i < 2; ++i) { // it's probably ok to consider just two quadrants?
        for(int i = 0; i < N; ++i) {
            auto a = v[i];
            cur[i][2] = a.first+a.second;
        }
        for(int i = 0; i < N; ++i) { // first octant
            auto a = v[i];
            cur[i][0] = a.first-a.second;
            cur[i][1] = a.second;
        }
        solve();
        for(int i = 0; i < N; ++i) { // second octant
            auto a = v[i];
            cur[i][0] = a.first;
            cur[i][1] = a.second-a.first;
        }
        solve();
        for(auto &a : v) a = {a.second,-a.first}; // rotate 90 degrees, repeat
    }
    return kruskal<lint>(ed);
}
