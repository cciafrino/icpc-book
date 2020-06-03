#include<bits/stdc++.h>
#define lint long long
#define st first
#define nd second

using namespace std;
template<typename T, typename Q> struct segtree_t {
    int n;
    vector<T> tree, og;
    vector<Q> lazy;
    segtree_t(int N) : n(N), tree(4*N), lazy(4*N) {}
    segtree_t(const vector<T> &other) : n(other.size()), og(other), 
    tree(4*n), lazy(4*n) { build(1, 0, n-1); }
    T f(const T &a, const T &b) { return max(a, b); }
    T build(int v, int l, int r) {
        lazy[v] = 0;
        if (l == r) return tree[v] = og[l];
        int m = l + (r - l)/2;
        return tree[v] = f(build(v<<1, l, m), build(v<<1|1, m+1, r));
    }
    void propagate(int v, int l, int r) {
        if (!lazy[v]) return; 
        int m = l + (r - l)/2;
        tree[v<<1] += lazy[v];
        tree[v<<1|1] += lazy[v];
        for (int i = 0; i < 2; ++i) lazy[v<<1|i] += lazy[v];
        lazy[v] = 0;
    }
    T query(int a, int b) { return query(a, b, 1, 0, n-1); }
    T query(int a, int b, int v, int l, int r) {
        if (b < l || r < a) return 0;
        if (a <= l && r <= b) return tree[v];
        propagate(v, l, r);
        int m = l + (r - l)/2;
        return f(query(a, b, v<<1,l, m), query(a, b, v<<1|1, m+1, r));
    }
    T update(int a, int b, Q delta) { return update(a, b, delta, 1, 0, n-1); }
    T update(int a, int b, Q delta, int v, int l, int r) {
        if (b < l || r < a) return tree[v];
        if (a <= l && r <= b) {
            tree[v] += delta;
            lazy[v] += delta;
            return tree[v];
        }
        propagate(v, l, r);
        int m = l + (r - l)/2;
        return tree[v] = f(update(a, b, delta, v<<1, l, m),
            update(a, b, delta, v<<1|1, m+1, r));
    }
};

using G = vector<vector<pair<int,int>>>;
template<typename T, bool USE_EDGES> struct heavylight_t {
	int t, n;
	vector<int> timer, preorder;
	vector<int> chain, par;
	vector<int> dep, sz;
	vector<T> val;
	heavylight_t() {}
	heavylight_t(G &g, int r = 0) : t(0), n(g.size()), par(n, -1), chain(n, -1), 
	dep(n), timer(n), sz(n),  val(n), preorder(n) { par[r] = chain[r] = r;
		dfs_sz(g, r), dfs_hld(g, r);  
	}
	int dfs_sz(G &g, int u) { 
		int subtree = 1;
		for(auto &e : g[u]) {
			int v = e.first;
			if (par[v] != -1) continue;
			par[v] = u; dep[v] = dep[u] + 1;
			subtree += dfs_sz(g, v);
			if (sz[v] > sz[g[u][0].first]) swap(g[u][0], e);
		}
		return sz[u] = subtree;
	}
	void dfs_hld(G &g, int u) {
		preorder[timer[u] = t++] = u;
		for (auto &e : g[u]) {
			int v = e.first;
			if (chain[v] != -1) continue;
			chain[v] = (e == g[u][0] ? chain[u] : v);
			dfs_hld(g, v);
			if (USE_EDGES) val[timer[v]] = e.second;
		}
	}
	template<class F> void path(int u, int v, F op) {
		if (u == v) return op(timer[u], timer[u]); 
		for(int e, p; chain[u] != chain[v]; u = p) {
			if (dep[chain[u]] < dep[chain[v]]) swap(u,v);
			u == (p = chain[u]) ? e = 0, p = par[u] : e = 1;
			op(timer[chain[u]] + e, timer[u]);
		}
		if (timer[u] > timer[v]) swap(u, v);
		op(timer[u] + USE_EDGES, timer[v]);
	}
};

template<typename T, bool USE_EDGES> struct lca_t {
	HLD<T, USE_EDGES> h;
	lca_t(const HLD<T, USE_EDGES> &g) : h(g) {}
	int kth_ancestor(int u, int k) const {	
		int kth = u;
		for(int p = h.chain[kth]; k && h.timer[kth]; kth = p, p = h.chain[kth]) {
			if (p == kth) p = h.par[kth];
			if (h.dep[kth] - h.dep[p] >= k) p = h.preorder[h.timer[kth]-k];
			k -= (h.dep[kth] - h.dep[p]);
		}
		return (k ? -1 : kth);
	}
	int lca(int u, int v) {
		if (u == v) return u;
		int x = h.timer[u];
		h.path(u, v, [&](int a,int b) { x = a - USE_EDGES; });
		return h.preorder[x];
	}
	int kth_on_path(int u, int v, int k) { //k 0-indexed
		int x = lca(u,v);		
		if (k > h.dep[u] + h.dep[v] - 2 * h.dep[x]) return -1;
		if (h.dep[u] - h.dep[x] > k) return kth_ancestor(u, k);
		return kth_ancestor(v, h.dep[u] + h.dep[v] - 2 * h.dep[x] - k );	
	}
};

template<typename T, bool USE_EDGES> struct hld_solver {
	heavylight_t<T, USE_EDGES> h;
	segtree_t<T, int> seg;
	hld_solver(const HLD<T, USE_EDGES> &g) : h(g), seg(h.val) {}
	void updatePath(int u, int v, T value) {
		h.path(u, v, [&](int a,int b) { seg.update(a, b, value); });
	}
	T queryPath(int u, int v) {
		T ans = 0;
		h.path(u, v, [&](int a,int b) { ans = max(ans, seg.query(a, b)); });
		return ans;
	}
	void updateEdge(int u, int v, T value) {
		int pos = h.timer[h.dep[u] < h.dep[v] ? v : u];
		seg.update(pos, pos, value);
	}
	T querySubtree(int v) { 
		return seg.query(h.timer[v] + USE_EDGES, h.timer[v] + h.sz[v] - 1);
	}
	void updateSubtree(int v, T value) {
		seg.update(h.timer[v] + USE_EDGES, h.timer[v] + h.sz[v] - 1, value);
	}
};

struct old_lca_t {
    int logn{0}, preorderpos{0};
    vector<int> invpreorder, height;
    vector<vector<int>> jump_binary, edges;
    old_lca_t(int n, vector<vector<int>>& G) : 
    edges(G), height(n), invpreorder(n) { 
        while((1<<(logn+1)) <= n) ++logn;
        jump_binary.assign(n+1, vector<int>(logn+1, 0));
        dfs(0, -1, 0);
    } 
    void dfs(int v, int p, int h) { 
        invpreorder[v] = preorderpos++;
        height[v] = h;
        jump_binary[v][0] = p < 0 ? v : p;
        for (int i = 1; i <= logn; ++i)
            jump_binary[v][i] = jump_binary[jump_binary[v][i-1]][i-1];
        for (int u : edges[v]) {
            if (u == p) continue; 
            dfs(u, v, h + 1);
        }
    }
    int climb(int v, int dist) { 
        for (int i = 0; i <= logn; ++i)
            if (dist & (1 << i)) v = jump_binary[v][i];
        return v;
    }
    int query(int a, int b) { 
        if (height[a] < height[b]) swap(a, b);
        a = climb(a, height[a] - height[b]);
        if (a == b) return a;
        for (int i = logn; i >= 0; --i)
            if (jump_binary[a][i] != jump_binary[b][i]) 
                a = jump_binary[a][i], b = jump_binary[b][i];
        return jump_binary[a][0];
    } 
    int dist(int a, int b) {
        return height[a] + height[b] - 2 * height[query(a,b)];
    }
    bool is_parent(int p, int v) { 
        if (height[p] > height[v]) return false;
        return p == climb(v, height[v] - height[p]);
    }
    bool on_path(int x, int a, int b) {
        int v = query(a, b);
        return is_parent(v, x) && (is_parent(x, a) || is_parent(x, b));
    }
    int get_kth_on_path(int a, int b, int k) {
        int v = query(a, b);
        int x = height[a] - height[v], y = height[b] - height[v];
        if (k > x + y) return -1;
        if (k < x) return climb(a, k);
        else return climb(b, x + y - k);
    }
};

struct bruteforce { 
	vector<vector<int>> tree;
	vector<int> vals;
	vector<int> pars;
	int unit = -1e9;
	int f(int a, int b) { return max(a, b); }
	void root(int cur, int p = -1) {
		pars[cur] = p;
		for (auto i: tree[cur]) {
			if (i != p) root(i, cur);
		}
	}
	bruteforce(vector<vector<int>> _tree): tree(_tree), vals((tree.size())), pars(tree.size()) {
		root(0);
	}
	bool dfsModify(int cur, int target, int val, int p=-1) {
		if (cur == target) {
			vals[cur] += val;
			return true;
		}
		bool alongPath = false;
		for (auto i: tree[cur]) {
			if (i == p) continue;
			alongPath |= dfsModify(i, target, val, cur);
		}
		if (alongPath) vals[cur] += val;
		return alongPath;
	}
	void modifyPath(int a, int b, int val) {
		dfsModify(a, b, val);
	}

	int dfsQuery(int cur, int target, int p = -1) {
		if (cur == target) {
			return vals[cur];
		}
		int res = unit;
		for (auto i: tree[cur]) {
			if (i == p) continue;
			res = f(res, dfsQuery(i, target, cur));
		}
		if (res != unit) {
			return f(res, vals[cur]);
		}
		return res;
	}
	int queryPath(int a, int b) {
		return dfsQuery(a, b);
	}
	int dfsSubtree(int cur, int p) {
		int res = vals[cur];
		for (auto i: tree[cur]) {
			if (i != p)
				res = f(res, dfsSubtree(i, cur));
		}
		return res;
	}
	int querySubtree(int a) {
		return dfsSubtree(a, pars[a]);
	}
};


namespace generate {
	vector<pair<int,int>> pruferCodeToTree(vector<int> &pruferCode) {
	    // Stores number count of nodes timer the prufer code
	    unordered_map<int,int> nodeCount;

	    // Set of integers absent timer prufer code. They are the leaves
	    set<int> leaves;

	    int len = pruferCode.size();
	    int node = len + 2;

	    // Count frequency of nodes
	    for ( int i = 0; i < len; i++ ) {
	        int t = pruferCode[i];
	        nodeCount[t]++;
	    }

	    // Find the absent nodes
	    for ( int i = 1; i <= node; i++ ) {
	        if ( nodeCount.find ( i ) == nodeCount.end() ) leaves.insert ( i );
	    }

	    vector<pair<int,int>> edges;
	    /*Connect Edges*/
	    for ( int i = 0; i < len; i++ ){
	        int a = pruferCode[i]; // First node

	        //Find the smallest number which is not present timer prufer code now
	        int b = *leaves.begin(); // the leaf

	        edges.push_back({a,b}); // Edge of the tree

	        leaves.erase ( b ); // Remove from absent list
	        nodeCount[a]--; // Remove from prufer code
	        if ( nodeCount[a] == 0 ) leaves.insert ( a ); // If a becomes absent
	    }

	    // The final edge
	    edges.push_back({*leaves.begin(), *leaves.rbegin()});
	    return edges;
	}

	vector<pair<int, int>> genRandomTree(int n) {
	    vector<int> pruferCode;
	    for (int i=0; i<n-2; i++) {
	        pruferCode.push_back(rand()%(n-1) + 1);
	    }
	    auto edges = pruferCodeToTree(pruferCode);
	    for (auto &p: edges)
	        p.first--, p.second--;
	    return edges;
	}	
}

void view_tree(vector<pair<int,int>> &tree) {
	for (auto i: tree) {
		cout << i.first << ' ' << i.second << endl;
        
    }
}

void test_n(int n, int num) {
    for (int out=0; out<num; out++) {
        auto G = generate::genRandomTree(n);
        vector<vector<pair<int, int>>> tree(n);
        vector<vector<int>> edges(n);
        for (auto i: G) {
            tree[i.first].push_back({i.second, 1});
            tree[i.second].push_back({i.first, 1});
            edges[i.first].push_back(i.second);
            edges[i.second].push_back(i.first);
        }
        heavylight_t<int, true> hl(tree);
        // view_tree(G);
        // LCA new_lca(tree);
        old_lca_t old_lca(n+1, edges);
        // old::LCA old_lca(tree);
        // New HLD
        lca_t<int,true> hld(hl);

        for (int i=0; i<100; i++) {
            int a = rand()%n, b = rand()%n;
            int RMQLca = old_lca.query(a, b);
            int HLDLca = hld.lca(a, b);
            int k = rand() % n;
            int KthLca = old_lca.get_kth_on_path(a, b, k);
            int KthHld = hld.kth_on_path(a, b, k);
            // cout << "{ " << a << ' ' << b << ' '<< k << " } : ";
            // cout << HLDLca << ' ' << RMQLca << endl;
            assert(HLDLca == RMQLca);
            assert(KthHld == KthLca);
        }
    }
}
void testAgainstBrute(int n, int iters, int queries) {
    for (int trees = 0; trees < iters; trees++) {
        auto graph = generate::genRandomTree(n);
        vector<vector<int>> tree1(n);
        vector<vector<pair<int,int>>> tree2(n);
        for (auto i : graph) {
            tree1[i.first].push_back(i.second);
            tree1[i.second].push_back(i.first);
            tree2[i.first].push_back({i.second, 1});
            tree2[i.second].push_back({i.first, 1});
        }
		int root = rand() % n;
        heavylight_t<int,false> hl(tree2);
        hld_solver<int, false> hld(hl);
		bruteforce hld2(tree1);
        for (int itr = 0; itr < queries; itr++) {
			int rng = rand() % 3;
            if (rng == 0) {
                int a = rand() % n;
				int b = rand() % n;
                int val = rand() % 10;
                hld.updatePath(a, b, val);
                hld2.modifyPath(a, b, val);
            } else if (rng == 1){
                int a = rand() % n;
                int b = rand() % n;
				hld.queryPath(a, b);
				hld2.queryPath(a, b);
                assert(hld.queryPath(a, b) == hld2.queryPath(a, b));
            } else if (rng == 2) {
				int a = rand() % n;
				assert(hld.querySubtree(a) == hld2.querySubtree(a));
			}
        }
    }

}

int main(){
	test_n(10, 1000);
    test_n(100, 100);
    test_n(1000, 10);
    test_n(1000, 1000);
	testAgainstBrute(5, 1000, 10000);
	testAgainstBrute(1000, 100, 100);
    cout<<"Tests passed!"<<endl;
}