/**
 * Author: Yuhao Du, Chris
 * Date: 2020-03-18
 * License: 
 * Source: Chinese Paper
 * Description: Highest label preflow push algorithm. Use it only if you really need the fastest maxflow algo. One limitation of the HLPP implementation is that you can't 
 * recover the weights for the full flow - use Dinic's for this.
 * Time: $O(V^2\sqrt E)$. Faster than Dinic with scaling(in practice). 
 * Status: Tested and stress-tested
 */
#include "../../content/various/LinkedList.h"

template <typename T, bool UseGlobal = true, bool UseGap = true>
struct HLPP {
    struct edge_t { int to, rev; T cap; };
    const T INF = numeric_limits<T>::max();
    int n, highest_active, highest;
    vector<vector<edge_t>> adj;
    vector<int> height, count, que;
    vector<T> excess;
    LinkedList list;
    DoublyLinkedList dlist;
    HLPP(int n) : n(n), adj(n), que(n), list(n), dlist(n) {}
    inline void addEdge(int from, int to, T cap, T rcap = 0) {
        adj[from].push_back({to, (int)adj[to].size(), cap});
        adj[to].push_back({from, (int)adj[from].size() - 1, rcap});
    }
    void globalRelabel(int t) {
        if (!UseGlobal) return;
        height.assign(n, n); height[t] = 0;
        count.assign(n, 0);
        int qh = 0, qt = 0;
        for (que[qt++] = t; qh < qt; ) {
            int u = que[qh++], h = height[u] + 1;
            for (edge_t &e : adj[u]) if (height[e.to] == n && adj[e.to][e.rev].cap > 0) {
                    count[height[e.to] = h] += 1;
                    que[qt++] = e.to;
                }
        }
        list.clear(); dlist.clear();
        for (int u = 0; u < n; ++u) if (height[u] < n) {
                dlist.insert(height[u], u);
                if (excess[u] > 0) list.push(height[u], u);
            }
        highest = highest_active = height[que[qt - 1]];
    }
    void push(int u, edge_t &e) {
        int v = e.to;
        T df = min(excess[u], T(e.cap));
        e.cap -= df, adj[v][e.rev].cap += df;
        excess[u] -= df, excess[v] += df;
        if (0 < excess[v] && excess[v] <= df) list.push(height[v], v);
    }
    void discharge(int u) {
        int nh = n;
        for (edge_t &e : adj[u]) if (e.cap > 0) 
                if (height[u] == height[e.to] + 1) {
                    push(u, e);
                    if (excess[u] == 0) return;
                } else nh = min(nh, height[e.to] + 1);
        int h = height[u];
        if (UseGap && count[h] == 1) {
            dlist.erase_all(h, highest, [&](int u) {
                count[height[u]]--, height[u] = n; });
            highest = h - 1;
        } else {
            count[h]--; dlist.erase(h, u);
            height[u] = nh;
            if (nh == n) return;
            count[nh]++; dlist.insert(nh, u);
            highest = max(highest, highest_active = nh);
            list.push(nh, u);
        }
    }
    T maxflow(int s, int t) {
        if (s == t) return 0;
        highest_active = 0; // highest label (active)
        highest = 0; // highest label (active and inactive)
        height.assign(n, 0); height[s] = n;
        for (int i = 0; i < n; ++i) if (i != s) dlist.insert(height[i], i);
        count.assign(n, 0); count[0] = n - 1;
        excess.assign(n, 0); excess[s] = INF; excess[t] = -INF;
        for (edge_t &e : adj[s]) push(s, e);
        globalRelabel(t);
        for (int u = -1, rest = n; highest_active >= 0; ) {
            if ((u = list.front(highest_active)) < 0) { --highest_active; continue; }
            list.pop(highest_active);
            discharge(u);
            if (--rest == 0) rest = n, globalRelabel(t);
        }
        return excess[t] + INF;
    }
};