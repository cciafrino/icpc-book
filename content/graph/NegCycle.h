/**
 * Author: Chris
 * Description: Detect negative cycle using BellmanFord Algorithm (algo see BellmanFord.h)
 * Source: https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html & BenQ
 * Status: tested on CSES1197
 * Time:
 * Details: If we follow the links back from u.b then we must always enter a cycle. 
 * Otherwise, this would contradict the assumption that there exists a shorter
 * path to u.b when considering paths of arbitrary length than those of 
 * length at most n-1. The sum of the edge weights along this path is
 * non-positive, and it cant be zero because then it would have no origin...
 */

struct edge_t { int a, b, w, s() { return a < b ? a : -a; }};
vector<int> negCyc(int n, vector<edge_t> edges) {
    vector<int64_t> d(n); 
    vector<int> p(n);
    int v = -1;
    for (int i = 0; i < n; ++i) {
        v = -1; 
        for (edge_t &u : edges)
            if (d[u.b] > d[u.a] + u.w) {
                d[u.b] = d[u.a] + u.w;
                p[u.b] = u.a, v = u.b;
            }
        if (v == -1) return {};
    }
    for (int i = 0; i < n; ++i) v = p[v]; // enter cycle
    vector<int> cycle = {v}; 
    while (p[cycle.back()] != v) cycle.push_back(p[cycle.back()]);
    return {cycle.rbegin(), cycle.rend()};
}