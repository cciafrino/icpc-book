/**
 * Author: Chris
 * Source: wesley-a-leung
 * Description: Trie implementation.
 * Time: 
 * Status: Fuzz-tested
 * Usage:
 */
 
struct Trie {
    struct node_t { 
    	unordered_map<char, node_t*> child; 
    	int cnt = 0, prefixCnt = 0; 
    } *root = new node_t();
    void add(node_t *v, const string &s) {
        node_t *cur = v;
        for (char c : s) {
            if (cur->child.count(c)) cur = cur->child[c];
            else cur = cur->child[c] = new node_t();
            cur->prefixCnt++;
        }
        cur->cnt++;
    }
    int count(node_t *v, const string &s) {
        node_t *cur = v;
        for (char c : s) {
            if (cur->child.count(c)) cur = cur->child[c];
            else return 0;
        }
        return cur->cnt;
    }
    int prefixCount(node_t *v, const string &s) {
        node_t *cur = v;
        for (char c : s) {
            if (cur->child.count(c)) cur = cur->child[c];
            else return 0;
        }
        return cur->prefixCnt;
    }
    Trie() {}
    void add(const string &s) { add(root, s); }
    bool contains(const string &s) { return count(root, s) >= 1; }
    bool hasPrefix(const string &s) { return prefixCount(root, s) >= 1; }
    int count(const string &s) { return count(root, s); }
    int prefixCount(const string &s) { return prefixCount(root, s); }
};