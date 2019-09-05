/**
 * Author: Benjamin Qi
 * Date: 
 * Source: Source: http://codeforces.com/blog/entry/13959
 * Description: maintains tree of palindromes
 * Time: 
 */
 
struct palindromic_t {
    static const int sigma = 26;
    vector<int> s, len, link, oc;
    vector<vector<int>> to;
    int idx, last, sz;
    palTree(int n) : s(n), len(n), link(n), oc(n) {
        to = vector<vector<int>>(n, vector<int>(n));
        s[idx++] = -1;
        link[0] = 1;
        len[1] = -1;
        sz = 2;
    }
    int getLink(int v) {
        while (s[idx-len[v]-2] != s[idx-1]) v = link[v];
        return v;
    }
    void addChar(int c) {
        s[idx++] = c;
        last = getLink(last);
        if (!to[last][c]) {
            len[sz] = len[last]+2;
            link[sz] = to[getLink(link[last])][c];
            to[last][c] = sz++;
        }
        last = to[last][c]; oc[last] ++;
    }
    void build() { // number of occurrences of each palindrome
        vector<pair<int,int>> v; 
        for(int i = 2; i < sz; ++i) v.push_back({len[i],i});
        sort(v.begin(),v.end()); reverse(v.begin(),v.end());
        for(auto a : v) oc[link[a.s]] += oc[a.s];
    }
};

