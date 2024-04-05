#include<bits/stdc++.h>
using namespace std;

#include "../../content/strings/suffix-automaton.h"

// struct array_state {
//     array<int, 26> as;
//     array_state() { fill(begin(as), end(as), ~0); }
//     int& operator[](char c) { return as[c - 'a']; }
//     int count(char c) { return (~as[c - 'a'] ? 1 : 0); }
// };

// template<typename Char, typename state = map<Char, int>> struct suffix_automaton {
//     struct node_t {
//         int len, link;
//         int64_t cnt;
//         state next;
//     };
//     int N, cur;
//     vector<node_t> nodes;
//     suffix_automaton() : N(1), cur(0), nodes{node_t{0, -1, 0, {}}} {}
//     node_t& operator[](int v) { return nodes[v]; };
//     void append(Char c) {
//         int v = cur; cur = N++;
//         nodes.push_back(node_t{nodes[v].len + 1, 0, 1, {}});
//         for (; ~v && !nodes[v].next.count(c); v = nodes[v].link) {
//             nodes[v].next[c] = cur;
//         }
//         if (~v) {
//             const int u = nodes[v].next[c];
//             if (nodes[v].len + 1 == nodes[u].len) {
//                 nodes[cur].link = u;
//             } else {
//                 const int clone = N++;
//                 nodes.push_back(nodes[u]);
//                 nodes[clone].len = nodes[v].len + 1;
//                 nodes[u].link = nodes[cur].link = clone;
//                 for (; ~v && nodes[v].next[c] == u; v = nodes[v].link) {
//                     nodes[v].next[c] = clone;
//                 }
//             }
//         }
//     }
// };

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit | cin.eofbit | cin.badbit);
    // string S = "abbdabcs";
    // do {
    //     suffix_automaton_t old_sa(size(S));
    //     suffix_automaton<char, array_state> new_sa;

    //     for (char c : S) {
    //         new_sa.append(c);
    //         old_sa.add(c);
    //     }

    //     for (int i = 0; i < size(new_sa.nodes); ++i) {
    //         assert(new_sa.nodes[i].len == old_sa.nodes[i]->len);
    //         assert(new_sa.nodes[i].link == (i ? old_sa.nodes[i]->link->id : -1));
    //     }
    // } while (next_permutation(S.begin(), S.end()));

    // cout << "Test passed" << endl;
    cout << "Skipped: still need to be implemented!" << endl;
}
