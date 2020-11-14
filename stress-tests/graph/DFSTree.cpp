#include<bits/stdc++.h>

using namespace std;

int old_prof = 0;

#include "../../content/graph/DFSTree.h"
#define rep(i, a, b) for(int i = a; i < (b); ++i)
 
struct old_tree_t {
    int timer, n;
    vector<vector<int>> edges;
    vector<pair<int,int>> bridges;
    vector<int> depth, mindepth, parent, st, child;
    vector<bool> cut;
    old_tree_t(int n) : n(n), timer(0), edges(n), parent(n,-1),
        mindepth(n,-1), depth(n,-1), st(n,-1) {}
    void addEdge(int a, int b) { 
        edges[a].push_back(b); edges[b].push_back(a);
    }
    void dfs(int v, int r = 0){
    	old_prof = max(old_prof, r);
        st[v] = timer; 
        mindepth[v] = depth[v];
        for (int u : edges[v]) {
            if (u == parent[v]) continue;
            if (st[u] == timer) {
                mindepth[v] = min(mindepth[v], depth[u]);
                continue;
            }
            depth[u] = 1 + depth[v];
            parent[u] = v;
            dfs(u, r+1);
            mindepth[v] = min(mindepth[v], mindepth[u]);
        }
    }
    vector<pair<int,int>> find_bridges() {
        for (int i = 0; i < n; ++i)  
            if (parent[i] != -1 && mindepth[i] == depth[i]) 
                bridges.push_back({parent[i], i});
        return bridges;
    }
    vector<bool> find_cut() {
        cut.resize(n), child.resize(n);
        for (int i = 0; i < n; ++i) 
            if (parent[i] != -1 && mindepth[i] >= depth[parent[i]]) 
                cut[parent[i]] = 1;
        for (int i = 0; i < n; ++i) 
            if (parent[i] != -1) child[parent[i]]++;
        for (int i = 0; i < n; ++i) 
            if (parent[i] == -1 && child[i] < 2) cut[i] = 0;
        return cut;
    }
    void solve() {
        for (int i = 0; i < n; ++i) 
            if (depth[i] == -1) {
                depth[i] = 0; parent[i] = -1;
                ++timer;
                dfs(i);
            }
    }
};


using pii = pair<int,int>;
using ll = long long;

int randRange(int hi) {
    return rand() % hi;
}

bool randBool() {
	return randRange(2);
}

vector<pii> randomSimpleGraphAsEdgeList(int n, int m) {
	assert(m <= (ll)n * (n - 1) / 2); 
	vector<pii> ed;
	if (m > (ll)n * n / 3) { 
		rep(i,0,n) rep(j,0,i) {
			int a = i, b = j;
			if (randBool()) swap(a, b);
			ed.push_back({a,b});
		}
		random_shuffle(ed.begin(), ed.end());//shuffle_vec(ed);
		ed.erase(ed.begin() + m, ed.end());
	} else {
		set<pii> seen;
		rep(i,0,m) { 
			int a = randRange(n);
			int b = randRange(n);
			if (a == b) continue;
			if (!seen.insert(minmax(a, b)).second) continue;
			ed.push_back({a,b});
		}
	}
	return ed;
} 

int main(){ 
	srand(time(0));   

	for(int t = 0; t<30; t++){ 
		old_prof = 0;
		int n = 1 + rand()%int(1e5);
		int m = (int) rand()%(min((ll)1e6, (ll(n) * ll (n-1))/2LL )); 
		
		auto edges = randomSimpleGraphAsEdgeList(n, m);
		
		old_tree_t old_tree(n);
		tree_t cur_tree(n); 
		for(auto &ed: edges){
			int u, v; tie(u,v) = ed;
			//cout<<u<<" "<<v<<"\n";
			old_tree.addEdge(u, v);
			cur_tree.addEdge(u, v);
		}
		cout<<"n: "<<n<<" m: "<<edges.size()<<"\n";
		
		cout<<"old\n";
		old_tree.solve();
		cout<<"new\n";
		cur_tree.solve();  
	     
 		vector<bool> old_cut = old_tree.find_cut();
		vector<bool> cur_cut = cur_tree.art;
		assert(old_cut == cur_cut);
		
 		auto old_brid = old_tree.find_bridges();
 		vector<bool> cur_brid = cur_tree.bridges;
 		sort(old_brid.begin(), old_brid.end());
 		
 		int num_cur_brid = 0;
 		for(int pos=0;pos<cur_tree.m;pos += 2){
 			if(! cur_brid[pos] ) continue;
 			num_cur_brid++;
 			auto ed = cur_tree.getEdge(pos);
 			if(!binary_search(old_brid.begin(), old_brid.end(), pii(ed[0], ed[1])) &&
 			   !binary_search(old_brid.begin(), old_brid.end(), pii(ed[1], ed[0]))
 			){
 				cout<<"cur bridge, not old bridge\n";
 				assert(0);
 			} 		
 		}
 		
 		assert(num_cur_brid == (int) old_brid.size()); 
 		
		
		
			
	}

	return 0;
}



