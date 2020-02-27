#include<bits/stdc++.h>

using namespace std;
#include "../../content/graph/LCA.h"
#include "../../content/graph/LCA.cpp"
#include "../../content/graph/TreePower.h"
using lint = long long;

/*
  Prufer Code to Tree
  Complexity: O(VlogV)
 */

vector<pair<int,int>> pruferCodeToTree(vector<int> &pruferCode) {
    // Stores number count of nodes in the prufer code
    unordered_map<int,int> nodeCount;

    // Set of integers absent in prufer code. They are the leaves
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

        //Find the smallest number which is not present in prufer code now
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

void dfsx(vector<vector<pair<int, int>>> &tree, int cur, int p, int d, vector<int> &par, vector<int> &depth) {
    par[cur] = p;
    depth[cur] = d;
    for(auto i: tree[cur]) {
        if (i.first == p) continue;
        dfsx(tree, i.first, cur, d+1, par, depth);
    }
}

void test_n(int n, int num) {
    for (int out=0; out<num; out++) {
        auto graph = genRandomTree(n);
        last_seen.resize(n);
        depth.resize(n);
        edges.resize(n);
        vector<vector<pair<int, int>>> tree(n);
        for (auto i: graph) {
            tree[i.first].push_back({i.second, 1});
            tree[i.second].push_back({i.first, 1});
            edges[i.first].push_back(i.second);
            edges[i.second].push_back(i.first);
        }
        precalc();
        vector<int> par(n), d(n);
        dfsx(tree, 0, 0, 0, par, d);
        vector<vector<int>> tbl = treeJump(par);
        // LCA new_lca(tree);
        lca_t old_lca(n+1, edges);
        // old::LCA old_lca(tree);
        for (int i=0; i<100; i++) {
            int a = rand()%n, b = rand()%n;
            int RMQLca = lca(a, b);
            int RMQDist = depth[a] + depth[b] - 2*depth[RMQLca];
            int binLca = lca(tbl, d, a, b);
            int binDist = d[a] + d[b] - 2*d[binLca];
            assert(RMQDist == old_lca.dist(a,b));
            assert(binDist == RMQDist);
        }
    }
}

signed main() {
    test_n(10, 1000);
    test_n(100, 100);
    test_n(1000, 10);
    cout<<"Tests passed!"<<endl;
}