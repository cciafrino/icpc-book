/**
 * Author: Chris
 * Description: Find the minimum spanning tree. Better for dense graphs.
 * Time: $O(E \log V)$
 */

struct prim_t {
    int n;
    vector<vector<pair<int,int>>> edges;
    vector<bool> chosen;
    priority_queue<pair<int, int>> pq;
    prim_t(int _n) : n(_n), edges(n), chosen(n, false) {}
    void process(int u) { //inicializa com process(0)
        chosen[u] = true;
        for (int j = 0; j < (int) edges[u].size(); j++) {
            pair<int, int> v = edges[u][j];
            if (!chosen[v.first]) pq.push(make_pair(-v.second, -v.first));
        }
    }
    int solve() {
        int mst_cost = 0;
        while (!pq.empty()) {
            pair<int,int> front = pq.top();
            pq.pop();
            int u = -front.second, w = -front.first;
            if (!chosen[u]) mst_cost += w;
	        process(u);
        }
        return mst_cost;
    }
};
