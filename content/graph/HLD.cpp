/**
 * Author: Johan Sannemo
 * Date: 2015-02-10
 * License: CC0
 * Source: folkore
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 *  edges such that the path from any leaf to the root contains at most log(n)
 *  light edges. The function of the HLD can be changed by modifying T, LOW and
 *  f. f is assumed to be associative and commutative.
 * Usage:
 *  HLD<int> hld(G);
 *  hld.update(index, value);
 *  tie(value, lca) = hld.query(n1, n2);
 * Status: Tested at SPOJ
 */
#include "SegTree.h"
template<typename T>
struct HLD {
    struct node_t {
        int d, par, val, chain = -1, pos = -1;
    };
    struct chain_t {
        int par, val;
        vector<int> nodes;
        tree_t<T> tree;
    };
    const T LOW = 0;
    void f(T& a, T b) { a = (a + b); }
    vector<node_t> V;
    vector<chain_t> C;
    HLD(vector<vpi>& g) : V(g.size()) {
        dfs(0, -1, g, 0);
        for(auto &c : C) {
            c.tree = {c.nodes.size()};
            for (int ni : c.nodes)
                c.tree.update(V[ni].pos, V[ni].val);
        }
    }
    void update(int node, T val) {
        node_t& n = V[node]; n.val = val;
        if (n.chain != -1) C[n.chain].tree.update(n.pos, val);
    }
    int pard(node_t& nod) {
        if (nod.par == -1) return -1;
        return V[nod.chain == -1 ? nod.par : C[nod.chain].par].d;
    }
    // query all *edges* between n1, n2
    pair<T, int> query(int i1, int i2) {
        T ans = LOW;
        while(i1 != i2) {
            node_t n1 = V[i1], n2 = V[i2];
            if (n1.chain != -1 && n1.chain == n2.chain) {
                int lo = n1.pos, hi = n2.pos;
                if (lo > hi) swap(lo, hi);
                f(ans, C[n1.chain].tree.query(lo, hi));
                i1 = i2 = C[n1.chain].nodes[hi];
            } else {
                if (pard(n1) < pard(n2))
                    n1 = n2, swap(i1, i2);
                if (n1.chain == -1)
                    f(ans, n1.val), i1 = n1.par;
                else {
                    chain_t& c = C[n1.chain];
                    f(ans, n1.pos ? c.tree.query(n1.pos, c.nodes.size())
                                  : c.tree.s[1]);
                    i1 = c.par;
                }
            }
        }
        return {ans, i1};
    }
    // query all *nodes* between n1, n2
    pair<T, int> query2(int i1, int i2) {
        pair<T, int> ans = query(i1, i2);
        f(ans.first, V[ans.second].val);
        return ans;
    }
    pii dfs(int at, int par, vector<vpi>& g, int d) {
        V[at].d = d; V[at].par = par;
        int sum = 1, ch, nod, sz;
        tuple<int,int,int> mx(-1,-1,-1);
        for(auto &e : g[at]){
            if (e.first == par) continue;
            tie(sz, ch) = dfs(e.first, at, g, d+1);
            V[e.first].val = e.second;
            sum += sz;
            mx = max(mx, {sz, e.first, ch});
        }
        tie(sz, nod, ch) = mx;
        if (2*sz < sum) return {sum, -1};
        if (ch == -1) { ch = C.size(); C.emplace_back(); }
        V[nod].pos = C[ch].nodes.size();
        V[nod].chain = ch;
        C[ch].par = at;
        C[ch].nodes.push_back(nod);
        return {sum, ch};
    }
};