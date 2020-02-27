/**
 * Author: Neal Wu
 * Date: 
 * Source: 
 * Description: Performs a preprocessing to enable querying the maximum/minimum edge weight on any path in a tree in constant time.
 * Time: $O(n\log(n))$
 */

#include<RMQ.h>

struct UF {
    vector<int> parent, size, left, right;
    UF(int n) : parent(n), size(n, 1), left(n), right(n) {
        for (int i = 0; i < n; i++)
            parent[i] = left[i] = right[i] = i;
    }
    int find(int x) {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }
    pair<int, int> unite(int x, int y) {
        x = find(x);
        y = find(y);
        assert(x != y);
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        pair<int,int> result = {right[x], left[y]};
        right[x] = right[y];
        return result;
    }
};

template<typename T>
struct linetree_t {
	struct edge_t {
		int u, v; T w;
		edge_t() {}
		edge_t(int a, int b, T c) : u(a), v(b), w(c) {}
		bool operator<(const edge_t &other) const {
			return w < other.w;
		} 
	};
	int n;
	const T limit = numeric_limits<T>::min();
	vector<int> index, line;
	vector<edge_t> edges; vector<T> line_w;
	unique_ptr<rmq_t<T>> rmq;
	linetree_t(int _n) : n(_n), index(n) {}
	void addEdge(int from, int to, T weight) {
		edges.emplace_back(from, to, weight);
	}
	void make_tree() {
		sort(edges.begin(), edges.end());
		UF dsu(n);
		vector<int> next_v(n, -1), has_prev(n);
		vector<T> next_w(n, limit);
		for (edge_t& e : edges) {
			pair<int, int> united = dsu.unite(e.u, e.v);
			next_v[united.first] = united.second;
			has_prev[united.second] = 1;
			next_w[united.first] = e.w;
		}
		int start = -1;
		for (int i = 0; i < n; ++i)
			if (!has_prev[i]) {
				start = i;
				break;
			}
		while(start >= 0) {
			line.push_back(start);
			if (next_v[start] >= 0) 
				line_w.push_back(next_w[start]);
			start = next_v[start];
		}
		for (int i = 0; i < n; ++i)
			index[line[i]] = i;
		rmq.reset(new RMQ<T>(line_w));
	}
	T query(int a, int b) {
		if (a == b) return limit;
		a = index[a], b = index[b];
		if (a > b) swap(a, b);
		return rmq->query(a-1, b-1).first;
	}
};
