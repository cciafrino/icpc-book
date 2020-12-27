/**
 * Author: Chris
 * Date: 2020-12-26
 * Description: Suffix automaton
 * Status: slightly-tested
 */
struct suffix_automaton_t {
    struct node_t {
        node_t* link; // parent state 
        int len, id; // length of the longest string in id'th class
        bool cloned;
        map<char, node_t*> next; // transitions (consider using an array instead)
        node_t() {}
        node_t(node_t* lnk, int t, int i, bool c) : link(lnk), len(t), 
            id(i), cloned(c) {}
        int get_longest() const { return len; }
        int get_shortest() const { return (link == nullptr ? 0 : 1 + link->len); }
        void set_next(char c, node_t* nxt) { next[c] = nxt; }
        bool has_next(char c) { return next.count(c); }
        node_t* get_next(char c) { return has_next(c) ? next[c] : nullptr; }
        vector<pair<char, node_t*>> get_transitions() {
            vector<pair<char, node_t*>> locs;
            for (auto x : next) locs.push_back(x);
            return locs;
        }
    };

    int size;
    node_t* top;
    vector<node_t*> nodes;

    suffix_automaton_t(const int N) : size(0), nodes(2 * N) {
        top = nodes.front() = make_node(0, false);
    }

    suffix_automaton_t(const string& S) : size(0), nodes(2 * int(S.size())) {
        top = nodes.front() = make_node(0, false);
        for (char c : S) {
            add(c);
        }
        topo_sort();
    }

    node_t* make_node(int len, bool is_clone) {
        nodes[size] = new node_t(nullptr, len, size, is_clone);
        return nodes[size++];
    }

    void add(char c) {
        node_t* cur = make_node(1 + top->len, false);
        node_t* par;

        for (par = top; par && !par->has_next(c); par = par->link) {
            par->set_next(c, cur);
        }

        if (par == nullptr) {
            cur->link = nodes[0];
        } else {
            node_t* Q = par->get_next(c);
            if (1 + par->len == Q->len) {
                cur->link = Q;
            } else {
                node_t* clone = make_node(1 + par->len, true);
                clone->next = Q->next;
                clone->link = Q->link;

                for (; par != nullptr && par->get_next(c) == Q; par = par->link) 
                    par->set_next(c, clone);

                Q->link = cur->link = clone;
            }
        }
        top = cur;
    }

    void topo_sort() {
        vector<int> indeg(size);
        vector<node_t*> order(size);
        for (int v = 0; v < size; ++v) {
            auto trans = nodes[v]->get_transitions();
            for (auto x : trans) {
                ++indeg[x.second->id];
            }
        }
        
        order[0] = nodes[0];
        int cur = 1;

        for (int v = 0; v < size; ++v) {
            node_t* r = order[v];
            auto trans = nodes[r->id]->get_transitions();
            for (auto x : trans) {
                if (--indeg[x.second->id] == 0)
                    order[cur++] = x.second;
            }
        }

        nodes = order;
        for (int v = 0; v < size; ++v)
            nodes[v]->id = v;
    }

    vector<int> get_terminals() {
        vector<int> terminals;
        for (auto par = top; par; par = par->link)
            terminals.push_back(par->id);
        return terminals;
    }

    int get_distinct() {
        int cnt = 0;
        for (int v = 0; v < size; ++v) {
            cnt += nodes[v]->len - (nodes[v]->link == nullptr ? 0 : nodes[v]->link->len);
        }
        return cnt;
    }
};

