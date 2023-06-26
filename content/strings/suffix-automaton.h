/**
 * Author: Chris
 * Date: 2021
 * Description: Suffix automaton
 * Status: stress-tested 
 */
template<int offset = 'a'> struct array_state {
	array<int, 26> as;
	array_state() { fill(begin(as), end(as), ~0); }
	int& operator[](char c) { return as[c - offset]; }
	int count(char c) { return (~as[c - offset] ? 1 : 0); }
};

template<typename Char, typename state = map<Char, int>> struct suffix_automaton {
	struct node_t {
		int len, link; int64_t cnt;
		state next;
	};
	int N, cur;
	vector<node_t> nodes;
	suffix_automaton() : N(1), cur(0), nodes{node_t{0, -1, 0, {}}} {}
	node_t& operator[](int v) { return nodes[v]; };
	void append(Char c) {
		int v = cur; cur = N++;
		nodes.push_back(node_t{nodes[v].len + 1, 0, 1, {}});
		for (; ~v && !nodes[v].next.count(c); v = nodes[v].link) {
			nodes[v].next[c] = cur;
		}
		if (~v) {
			const int u = nodes[v].next[c];
			if (nodes[v].len + 1 == nodes[u].len) {
				nodes[cur].link = u;
			} else {
				const int clone = N++;
				nodes.push_back(nodes[u]);
				nodes[clone].len = nodes[v].len + 1;
				nodes[u].link = nodes[cur].link = clone;
				for (; ~v && nodes[v].next[c] == u; v = nodes[v].link) {
					nodes[v].next[c] = clone;
				}
			}
		}
	}
};
