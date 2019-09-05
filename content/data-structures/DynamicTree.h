/**
 * Author: halyavin
 * Description: Dynamic Segment 
 */
struct Edge {
    int from;
    int to;
    int64_t capacity;
    int64_t flow;
};
 
struct Node {
    static constexpr uint32_t null = uint32_t(-1);
    uint32_t left = null;
    uint32_t right = null;
    uint32_t parent = null;
    int dv;
    int min;
    Node() : dv(0), min(0) {}
    Node(int value) : dv(value), min(0) {}
};
 
template<class E, bool oriented = false>
struct DynamicTree {
    static int capacity(int v, E* edge) {
        if (edge->from == v) {
            return edge->capacity - edge->flow;
        } else {
            return oriented ? edge->flow : edge->flow + edge->capacity;
        }
    }
 
    static void setCapacity(int v, E* edge, int cap) {
        if (edge->from == v) {
            edge->flow = edge->capacity - cap;
        } else {
            edge->flow = oriented ? cap : cap - edge->capacity;
        }
    }
 
    std::vector<E*> parentEdges;
    std::vector<Node> nodes;
 
    bool isRoot(uint32_t node) {
        uint32_t parent = nodes[node].parent;
        return parent == Node::null || (nodes[parent].left != node && nodes[parent].right != node);
    }
 
    void fixMin(uint32_t node) {
        int result = 0;
        uint32_t left = nodes[node].left;
        if (left != Node::null) {
            result = std::min(result, nodes[left].min + nodes[left].dv);
        }
        uint32_t right = nodes[node].right;
        if (right != Node::null) {
            result = std::min(result, nodes[right].min + nodes[right].dv);
        }
        nodes[node].min = result;
    }
 
    void rotate(uint32_t node) {
        uint32_t parent = nodes[node].parent;
        uint32_t middle;
        if (nodes[parent].left == node) {
            middle = nodes[node].right;
            nodes[node].right = parent;
            nodes[parent].left = middle;
        } else {
            middle = nodes[node].left;
            nodes[node].left = parent;
            nodes[parent].right = middle;
        }
        nodes[node].parent = nodes[parent].parent;
        uint32_t grandparent = nodes[node].parent;
        if (grandparent != Node::null) {
            if (nodes[grandparent].left == parent) {
                nodes[grandparent].left = node;
            } else if (nodes[grandparent].right == parent) {
                nodes[grandparent].right = node;
            }
        }
        nodes[parent].parent = node;
        int dNode = nodes[node].dv;
        int dParent = nodes[parent].dv;
        nodes[node].dv += dParent;
        nodes[parent].dv = -dNode;
        if (middle != Node::null) {
            nodes[middle].dv += dNode;
            nodes[middle].parent = parent;
        }
        fixMin(parent);
        fixMin(node);
    }
 
    void splay(uint32_t node) {
        while (!isRoot(node)) {
            uint32_t parent = nodes[node].parent;
            if (isRoot(parent)) {
                rotate(node);
                return;
            }
            uint32_t grandParent = nodes[parent].parent;
            if ((nodes[parent].left == node) == (nodes[grandParent].left == parent)) {
                rotate(parent);
            } else {
                rotate(node);
            }
            rotate(node);
        }
    }
 
    uint32_t pathRoot(uint32_t node) {
        while (true) {
            uint32_t right = nodes[node].right;
            if (right == Node::null) return node;
            node = right;
        }
    }
 
    void expose(uint32_t node) {
        splay(node);
        while (true) {
            uint32_t parent = nodes[node].parent;
            if (parent == Node::null) break;
            splay(parent);
            uint32_t left = nodes[parent].left;
            if (left != Node::null) {
                nodes[left].dv += nodes[parent].dv;
            }
            if (nodes[parent].parent == Node::null && nodes[parent].right == Node::null) {
                nodes[parent].dv = std::numeric_limits<int>::max();
                nodes[parent].min = 0;
            }
            nodes[parent].left = node;
            nodes[node].dv -= nodes[parent].dv;
            // fixMin(parent); // fixed by rotate
            rotate(node);
        }
    }
 
    uint32_t getRoot(uint32_t node) {
        expose(node);
        return pathRoot(node);
    }
 
    uint32_t disconnectRoot(uint32_t root) {
        uint32_t newRoot = root;
        if (nodes[newRoot].left == Node::null) {
            newRoot = nodes[newRoot].parent;
        } else {
            newRoot = nodes[newRoot].left;
            while (nodes[newRoot].right != Node::null) {
                newRoot = nodes[newRoot].right;
            }
        }
        splay(newRoot);
        nodes[newRoot].parent = Node::null;
        nodes[newRoot].right = Node::null;
        nodes[root].parent = Node::null;
        nodes[root].dv = std::numeric_limits<int>::max();
        nodes[root].min = 0;
        setCapacity(newRoot, parentEdges[newRoot], nodes[newRoot].dv);
        parentEdges[newRoot] = nullptr;
        if (nodes[newRoot].left != Node::null) {
            nodes[nodes[newRoot].left].dv += nodes[newRoot].dv - std::numeric_limits<int>::max();
        }
        nodes[newRoot].dv = std::numeric_limits<int>::max();
        nodes[newRoot].min = 0;
        return newRoot;
    }
 
    void disconnectVertex(uint32_t u) {
        splay(u);
        uint32_t v = nodes[u].right;
        nodes[u].right = Node::null;
        nodes[v].dv += nodes[u].dv;
        nodes[v].parent = nodes[u].parent;
        nodes[u].parent = Node::null;
 
        setCapacity(u, parentEdges[u], nodes[u].dv);
        if (nodes[u].left != Node::null) {
            nodes[nodes[u].left].dv += nodes[u].dv - std::numeric_limits<int>::max();
        }
        nodes[u].dv = std::numeric_limits<int>::max();
        parentEdges[u] = nullptr;
        nodes[u].min = 0;
        if (nodes[v].left == Node::null && nodes[v].right == Node::null) {
            nodes[v].dv = std::numeric_limits<int>::max();
            nodes[v].min = 0;
        }
    }
 
    void link(uint32_t u, uint32_t v, Edge* edge) {
        splay(u);
        int cap = capacity(u, edge);
        int delta = cap - nodes[u].dv;
        nodes[u].dv = cap;
        if (nodes[u].left != Node::null) {
            nodes[nodes[u].left].dv -= delta;
        }
        fixMin(u);
        parentEdges[u] = edge;
        nodes[u].parent = v;
    }
 
    int getPathMin(uint32_t u) {
        splay(u);
        return nodes[u].min + nodes[u].dv;
    }
 
    void subtractPath(uint32_t u, int value) {
        splay(u);
        nodes[u].dv -= value;
        if (nodes[u].left != Node::null) {
            nodes[nodes[u].left].dv += value;
        }
        fixMin(u);
    }
 
    uint32_t findNonZeroPath(uint32_t u) {
        splay(u);
        int delta = nodes[u].dv;
        if (delta == 0) return u;
        uint32_t check = nodes[u].right;
        while (true) {
            delta += nodes[check].dv;
            uint32_t left = nodes[check].left;
            if (left == Node::null || delta + nodes[left].dv + nodes[left].min > 0) {
                if (delta == 0) {
                    return check;
                }
                check = nodes[check].right;
                continue;
            }
            check = left;
        }
    }
 
    void destroy(uint32_t v, int value) {
        value += nodes[v].dv;
        if (parentEdges[v] != nullptr) {
            setCapacity(v, parentEdges[v], value);
            parentEdges[v] = nullptr;
        }
        if (nodes[v].left != Node::null) {
            destroy(nodes[v].left, value);
        }
        if (nodes[v].right != Node::null) {
            destroy(nodes[v].right, value);
        }
    }
 
    void destroyAll() {
        for (uint32_t i = 0; i < nodes.size(); i++) {
            if (isRoot(i)) {
                destroy(i, 0);
            }
        }
    }
 
};
