/**
 * Author: Tiago Montalvão
 * Description: 
 */
 
struct Node {
    map<char, int> adj;
    int fail, next; 
    pair<int,int> match;
    void init() {
        adj.clear(); fail = -1; match = {-1,-1}; next = -1;
    }
    int getChild(const char &c) {
        auto it = adj.find(c);
        if (it != adj.end()) return it->second;
        return -1;
    }
};

int nNodes, nPatt;
Node trie[MAX];
void init() {
    trie[0].init();
    nNodes = 1; nPatt = 0;
} 
void add(const string &word) {
    int node = 0, aux = -1;
    for (char c : word) {
        aux = trie[node].getChild(c);
        if (aux == -1) {
            trie[nNodes].init();
            aux = nNodes +=1;
            trie[node].adj[c] = aux;
        }
        node = aux;
    }
    trie[node].match = {nPatt++, (int)word.size()};
}
void build() {
    queue<int> q;
    trie[0].fail = -1;
    q.push(0);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto it = trie[u].adj.begin(); it != trie[u].adj.end(); ++it) {
            int v = it->second;
            char c = it->first;
            q.push(v);
            int f = trie[u].fail;
            while(f >= 0 && trie[f].getChild(c) == -1) f = trie[f].fail;
            f = f >= 0 ? trie[f].getChild(c) : 0;
            trie[v].fail = f;
            trie[v].next = trie[f].match.first >= 0 ? f : trie[f].next;
        }
    }
}

void search(const string &text) {
    int node = 0;
    for (int i = 0; i < text.size(); ++i) {
        while(node >= 0 && trie[node].getChild(text[i]) == -1) node = trie[node].fail;
        node = node >= 0 ? trie[node].getChild(text[i]) : 0;
        int aux = node;
        while(aux >= 0) {
            if (trie[aux].match.first >= 0) {
                //do something with the match
                cout << "Pattern: " << trie[aux].match.first << ", pos: ";
                cout << i - trie[aux].match.second + 1 << '\n';
            }
            aux = trie[aux].next;
        }
    }
}
int newNode(int node, char c) {
    while(node >= 0 && trie[node].getChild(c) == -1) 
        node = trie[node].fail;
    return node >= 0 ? trie[node].getChild(c) : 0;
}


