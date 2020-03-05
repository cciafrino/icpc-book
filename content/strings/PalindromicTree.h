/**
 * Author: BenQ
 * Description: Used infrequently. Palindromic tree computes 
    * number of occurrences of each palindrome within string.
    * \texttt{ans[i][0]} stores min even number $x$ such that 
    * the prefix $s[1..i]$ can be split into exactly $x$
    * palindromes, \texttt{ans[i][1]} does the same for odd $x.$
 * Time: $O(N\sum)$ for addChar, $O(N\log N)$ for updAns
 * Source: http://codeforces.com/blog/entry/13959, https://codeforces.com/blog/entry/19193
 */

template<int SZ> struct PalTree {
    static const int sigma = 26;
    int s[SZ], len[SZ], link[SZ], to[SZ][sigma], oc[SZ];
    int slink[SZ], diff[SZ];
    array<int,2> ans[SZ], seriesAns[SZ];
    int n, last, sz;
    PalTree() { 
        s[n++] = -1; link[0] = 1; len[1] = -1; sz = 2; 
        ans[0] = {0,MOD};
    }
    int getLink(int v) {
        while (s[n-len[v]-2] != s[n-1]) v = link[v];
        return v;
    }
    void updAns() { // serial path has O(log n) vertices
        ans[n-1] = {MOD,MOD};
        for (int v = last; len[v] > 0; v = slink[v]) {
            seriesAns[v] = ans[n-1-(len[slink[v]]+diff[v])];
            if (diff[v] == diff[link[v]]) 
                for(int i = 0; i < 2; ++i) 
                    seriesAns[v][i] = min(seriesAns[v][i],seriesAns[link[v]][i]);
            // previous oc of link[v] coincides with start of last oc of v
            for(int i = 0; i < 2; ++i) 
                ans[n-1][i] = min(ans[n-1][i],seriesAns[v][i^1]+1);
        }
    }
    void addChar(int c) {
        s[n++] = c;
        last = getLink(last);
        if (!to[last][c]) {
            len[sz] = len[last]+2;
            link[sz] = to[getLink(link[last])][c];
            diff[sz] = len[sz]-len[link[sz]];
            if (diff[sz] == diff[link[sz]]) slink[sz] = slink[link[sz]];
            else slink[sz] = link[sz]; 
            // slink[v] = max suffix u of v such that diff[v]\neq diff[u]
            to[last][c] = sz++;
        }
        last = to[last][c]; oc[last] ++;
        updAns();
    }
    void numOc() { // # occurrences of each palindrome
        vector<pair<int,int>> v; 
        for(int i = 2; i < sz; ++i) v.push_back({len[i],i});
        sort(v.rbegin(), v.rend()); 
        for(auto& a : v) oc[link[a.second]] += oc[a.second];
    }
};


// vv Fmota's
class lg_parents {
public:
    vector<vector<int>> parents;
    void add_edge(int u, int v){
        reserve(u);
        reserve(v);
        vector<int> pv = {u};
        for(int i = 1; ; i++){
            int up = pv[i - 1];
            reserve(up);
            if(parents[up].size() >= i){
                pv.push_back(parents[up][i - 1]);
            } else {
                break;
            }
        }
        parents[v] = pv;
    }
private:
    void reserve(int u){
        while(parents.size() <= u) parents.emplace_back();
    }
};
struct eertree {
    vector<map<int,int>> to;
    vector<int> fail, len, text, dep;
    vector<long long> sum;
    int odd, even, last;
    int get_node(int l){
        to.emplace_back();
        fail.emplace_back(-1);
        len.emplace_back(l);
        dep.emplace_back();
        sum.emplace_back();
        return len.size() - 1;
    }
    int match(int node){
        int sz = text.size();
        for(; text[sz - len[node] - 2] != text[sz - 1]; node = fail[node]);
        return node;
    }
    int adj(int u, int c){
        auto it = to[u].find(c);
        if(it == to[u].end()) return -1;
        return it->second;
    }
    lg_parents ps;
    bool extend(int c){
        text.push_back(c);
        int now = match(last), p;
        if((p = adj(now, c)) != -1)
            return last = p, false;
        last = to[now][c] = get_node(len[now] + 2);
        if(now == odd) fail[last] = even;
        else {
            now = match(fail[now]);
            fail[last] = adj(now, c);
        }
        ps.add_edge(fail[last], last);
        solve(last);
        return true;
    }
    void solve(int u){
        int need = len[u] / 2;
        int at = u, pos = ps.parents[u].size() - 1;
        while(pos >= 0){
            if(ps.parents[at].size() <= pos) pos--;
            else {
                if(len[ps.parents[at][pos]] > need) at = ps.parents[at][pos];
                else pos--;
            }
        }
        int up = 0;
        if(ps.parents[at].size() > 0 && len[ps.parents[at][0]] == need){
            up = ps.parents[at][0];
        }
        dep[last] = dep[up] + 1;
        sum[last] = sum[fail[last]] + dep[last];
    }
    void init(){
        text.push_back(-1);
        last = even = get_node(0);
        odd = get_node(-1);
        fail[even] = odd;
        ps.add_edge(odd, even);
    }
    eertree(){ init(); }
};