/**
 * Author: 
 * Description: 
 * Status: Not Working on UVA 820
 */

struct Flow {
	int n;
	vector<vector<int> > graph; //list of id's
	vector<int> st, en, back; //back = back edge id
	vector<lint> f, c;
	vector<int> parent;
	Flow(int n): n(n), graph(n), parent(n){}
	void add_edge(int u, int v, int cap){ /// start-hash
		int id1 = st.size();
		int id2 = id1 + 1;
		st.push_back(u); st.push_back(v);
		en.push_back(v); en.push_back(u);
		back.push_back(id2); back.push_back(id1);
		f.push_back(0); f.push_back(0);
		c.push_back(cap); c.push_back(0);
		graph[u].push_back(id1);
		graph[v].push_back(id2);
	} /// end-hash
	void add(int id1, int v){ /// start-hash
		f[id1] += v;
		c[id1] -= v;
		f[back[id1]] -= v;
		c[back[id1]] += v;
	} /// end-hash
    lint maxflow(int s, int t){ /// start-hash
		lint ans = 0;
		vector<int> bfs;
		if(s == t) return ans;
		while(1){
			for(int i = 0; i < n; i++) parent[i] = -1;
			bfs.clear();
			bfs.push_back(s); parent[s] = -2;
			int cur = 0;
			while(cur < bfs.size()){
				int u = bfs[cur]; 
			    cur++;
				for(int u : graph[u]){
					if(c[u] == 0) continue;
					if(parent[en[u]] != -1) continue;
					parent[en[u]] = u;
					bfs.push_back(en[u]);
				}
			}
			if(parent[t] == -1) break;
			lint send = 4e18;
			int curv = t;
			while(parent[curv] != -2){
				send = min(send, c[parent[curv]]);
				curv = st[parent[curv]];
			}
			curv = t;
			while(parent[curv] != -2){
				add(parent[curv], send);
				curv = st[parent[curv]];
			}
			ans += send;
		}
		return ans;
	} /// end-hash
};
