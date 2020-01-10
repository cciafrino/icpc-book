/**
 * Author: chilli, Takanori MAEHARA
 * Date: 2019-05-10
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/graph/arborescence.cc
 * Description: Edmonds' algorithm for finding the weight of the minimum spanning
 * tree/arborescence of a directed graph, given a root node. If no MST exists, returns -1.
 * Time: O(E \log V)
 * Status: Stress-tested, also tested on NWERC 2018 fastestspeedrun
 */
#pragma once

#include "../data-structures/UnionFind.h"

struct edge_t { int a, b; lint w; };
struct Node { /// lazy skew heap node
    edge_t key;
    Node *l, *r;
    lint delta;
    void prop() {
        key.w += delta;
        if (l) l->delta += delta;
        if (r) r->delta += delta;
        delta = 0;
    }
    edge_t top() { prop(); return key; }
};
Node *merge(Node *a, Node *b) {
    if (!a || !b) return a ?: b;
    a->prop(), b->prop();
    if (a->key.w > b->key.w) swap(a, b);
    swap(a->l, (a->r = merge(b, a->r)));
    return a;
}
void pop(Node*& a) { a->prop(); a = merge(a->l, a->r); }

lint dmst(int n, int r, vector<edge_t>& g) {
    UF uf(n);
    vector<Node*> heap(n);
    for(auto &e : g) heap[e.b] = merge(heap[e.b], new Node{e});
    lint res = 0;
    vector<int> seen(n, -1), path(n);
    seen[r] = r;
    for(int s = 0; s < n; ++s) {
        int u = s, qi = 0, w;
        while (seen[u] < 0) {
            path[qi++] = u, seen[u] = s;
            if (!heap[u]) return -1;
            edge_t e = heap[u]->top();
            heap[u]->delta -= e.w, pop(heap[u]);
            res += e.w, u = uf.find(e.a);
            if (seen[u] == s) {
                Node* cyc = 0;
                do cyc = merge(cyc, heap[w = path[--qi]]);
                while (uf.unite(u, w));
                u = uf.find(u);
                heap[u] = cyc, seen[u] = -1;
            }
        }
    }
    return res;
}