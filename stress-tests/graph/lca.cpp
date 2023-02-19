#include "../utilities/template.h"
#undef sz
#include "../utilities/genTree.h"

#include "../../content/data-structures/rmq.h"
namespace euler_tour {
#include "../../content/graph/lca-euler-tour.h"
}

namespace binary_lifting {
#include "../../content/graph/lca-binary-lifting.h"
}

namespace old {
typedef vector<pii> vpi;
typedef vector<vpi> graph;

struct LCA {
    vi time;
    vector<ll> dist;
    rmq_t<pii> rmq;

    LCA(graph& C) : time(int(C.size()), -99), dist(int(C.size())), rmq(dfs(C)) {}

    vpi dfs(graph& C) {
        vector<tuple<int, int, int, ll>> q(1);
        vpi ret;
        int T = 0, v, p, d; ll di;
        while (!q.empty()) {
            tie(v, p, d, di) = q.back();
            q.pop_back();
            if (d) ret.emplace_back(d, p);
            time[v] = T++;
            dist[v] = di;
            for(auto &e: C[v]) if (e.first != p)
                q.emplace_back(e.first, v, d+1, di + e.second);
        }
        return ret;
    }

    int query(int a, int b) {
        if (a == b) return a;
        a = time[a], b = time[b];
        return rmq.query(min(a, b), max(a, b)).first;
    }
    ll distance(int a, int b) {
        int lca = query(a, b);
        return dist[a] + dist[b] - 2 * dist[lca];
    }
};
}


void getPars(vector<vi> &tree, int cur, int p, int d, vector<int> &par, vector<int> &depth) {
    par[cur] = p;
    depth[cur] = d;
    for(auto i: tree[cur]) if (i != p) {
        getPars(tree, i, cur, d+1, par, depth);
    }
}
void test_n(int n, int num) {
    for (int out=0; out<num; out++) {
        auto graph = genRandomTree(n);
        vector<vi> tree(n);
        vector<vector<pair<int, int>>> oldTree(n);
        for (auto i: graph) {
            tree[i.first].push_back(i.second);
            tree[i.second].push_back(i.first);
            oldTree[i.first].push_back({i.second, 1});
            oldTree[i.second].push_back({i.first, 1});
        }
        vector<int> par(n), depth(n);
        getPars(tree, 0, 0, 0, par, depth);
        binary_lifting::lca_t bl_lca(n, tree);
        euler_tour::lca_t rmq_lca(tree);
        for (int i=0; i<100; i++) {
            int a = rand()%n, b = rand()%n;
            int k = max(1, rand()) % max(1, rmq_lca.dist(a, b));
            int k2 = max(1, rand()) % max(1, bl_lca.height[a] - 1);
            int binLca = bl_lca.query(a, b);
            int newLca = rmq_lca.query(a,b);
            assert(binLca == newLca);
            assert(bl_lca.dist(a, b) == rmq_lca.dist(a, b));
            assert(bl_lca.get_kth_on_path(a, b, k) == rmq_lca.get_kth_node_on_path(a, b, k));

            int jmp_la = bl_lca.climb(a, k);
            int jmp_lb = rmq_lca.get_kth_ancestor(a, k);
            assert(jmp_la == (jmp_lb == -1 ? jmp_lb+1 : jmp_lb));
           
            int jmp_ra = bl_lca.climb(a, k);
            int jmp_rb = rmq_lca.get_kth_ancestor(a, k);
            assert(jmp_ra == (jmp_rb == -1 ? jmp_rb+1 : jmp_rb));
        }
    }
}

signed main() {
    test_n(10, 1000);
    test_n(100, 100);
    test_n(1000, 10);
    cout<<"Tests passed!"<<endl;
}

