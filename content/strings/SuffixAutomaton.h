/**
 * Author: 
 * Date: 
 * License: Unknown
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
template<typename Str>
struct suffix_automaton{
    typedef typename Str::value_type Char;
    struct node{
        int len = 0, link = -1, firstpos = -1;
        bool isclone = false;
        map<Char, int> next;
        vector<int> invlink;
        int cnt = -1;
    };
    vector<node> state = vector<node>(1);
    int last = 0;
    suffix_automaton(const Str &s){
        state.reserve(s.size());
        for(auto c: s) insert(c);
    }
    void insert(Char c){
        int cur = state.size();
        state.push_back({state[last].len + 1, -1, state[last].len});
        int p = last;
        while(p != -1 && !state[p].next.count(c)){
            state[p].next[c] = cur;
            p = state[p].link;
        }
        if(p == -1) state[cur].link = 0;
        else{
            int q = state[p].next[c];
            if(state[p].len + 1 == state[q].len) state[cur].link = q;
            else{
                int clone = state.size();
                state.push_back({state[p].len + 1, state[q].link, state[q].firstpos, true, state[q].next});
                while(p != -1 && state[p].next[c] == q){
                    state[p].next[c] = clone;
                    p = state[p].link;
                }
                state[q].link = state[cur].link = clone;
            }
        }
        last = cur;
    }
    void print(){
        for(int u = 0; u < state.size(); ++ u){
            cout << "--------------------------------\n";
            cout << "Node " << u << ": len = " << state[u].len << ", link = " << state[u].link;
            cout << ", firstpos = " << state[u].firstpos << ", cnt = " << state[u].cnt;
            cout << ", isclone = " << state[u].isclone;
            cout << "\ninvlink = " << state[u].invlink << "next = " << state[u].next;
            cout << "--------------------------------" << endl;
        }
    }
    pair<int, int> match(const Str &s){ // (Length of the longest prefix of s, state)
        int u = 0;
        for(int i = 0; i < s.size(); ++ i){
            if(!state[u].next.count(s[i])) return {i, u};
            u = state[u].next[s[i]];
        }
        return {s.size(), u};
    }
    vector<long long> distinct_substr_cnt(){
        vector<long long> dp(state.size());
        function<long long(int)> solve = [&](int u){
            if(dp[u]) return dp[u];
            dp[u] = 1;
            for(auto [c, v]: state[u].next) dp[u] += solve(v);
            return dp[u];
        };
        solve(0);
        return dp;
    }
    vector<long long> distinct_substr_len(){
        vector<long long> res(state.size()), dp(state.size());
        function<long long(int)> solve = [&](int u){
            if(dp[u]) return res[u];
            dp[u] = 1;
            for(auto [c, v]: state[u].next){
                res[u] += solve(v) + dp[v];
                dp[u] += dp[v];
            }
            return res[u];
        };
        solve(0);
        return res;
    }
    pair<Str, int> k_th_substr(long long k){
        vector<long long> dp(distinct_substr_cnt());
        assert(dp[0] >= k && k);
        Str res;
        int u = 0;
        for(; -- k; ) for(auto [c, v]: state[u].next){
            if(k > dp[v]) k -= dp[v];
            else{
                res.push_back(c);
                u = v;
                break;
            }
        }
        return {res, u};
    }
    pair<Str, int> smallest_substr(int length){
        Str res;
        int u = 0;
        for(; length --; ){
            assert(!state[u].next.empty());
            auto it = state[u].next.begin();
            res.push_back(it->first);
            u = it->second;
        }
        return {res, u};
    }
    pair<int, int> find_first(const Str &s){ // length, pos
        auto [l, u] = match(s);
        return {l, state[u].firstpos - int(s.size()) + 1};
    }
    void process_invlink(){
        for(int u = 1; u < int(state.size()); ++ u) state[state[u].link].invlink.push_back(u);
    }
    vector<int> find_all(const Str &s, bool invlink_init = false){
        auto [l, u] = match(s);
        if(l < int(s.size())) return{};
        vector<int> res;
        if(!invlink_init) process_invlink();
        function<void(int)> solve = [&](int u){
            if(!state[u].isclone) res.push_back(state[u].firstpos);
            for(auto v: state[u].invlink) solve(v);
        };
        solve(u);
        for(auto &x: res) x += 1 - int(s.size());
        sort(res.begin(), res.end());
        return res;
    }
    Str lcs(const Str &s){
        int u = 0, l = 0, best = 0, bestpos = 0;
        for(int i = 0; i < int(s.size()); ++ i){
            while(u && !state[u].next.count(s[i])){
                u = state[u].link;
                l = state[u].len;
            }
            if(state[u].next.count(s[i])){
                u = state[u].next[s[i]];
                ++ l;
            }
            if(l > best){
                best = l;
                bestpos = i;
            }
        }
        return {s.begin() + bestpos - best + 1, s.begin() + bestpos + 1};
    }
    vector<int> process_lcs(const Str &s){ // list of length ending at the pos
        int u = 0, l = 0;
        vector<int> res(s.size());
        for(int i = 0; i < int(s.size()); ++ i){
            while(u && !state[u].next.count(s[i])){
                u = state[u].link;
                l = state[u].len;
            }
            if(state[u].next.count(s[i])){
                u = state[u].next[s[i]];
                ++ l;
            }
            res[i] = l;
        }
        return res;
    }
    void process_cnt(bool invlink_init = false){
        for(int u = 0; u < int(state.size()); ++ u) state[u].cnt = (!state[u].isclone && u);
        if(!invlink_init) process_invlink();
        function<void(int)> solve = [&](int u){
            for(auto v: state[u].invlink){
                solve(v);
                state[u].cnt += state[v].cnt;
            }
        };
        solve(0);
    }
    int count(const string &s){
        assert(state[0].cnt != -1);
        return state[match(s).second].cnt;
    }
};
template<typename Str>
Str lcs(vector<Str> a){
    swap(a[0], *min_element(a.begin(), a.end(), [](const Str &s, const Str &t){ return s.size() < t.size(); }));
    vector<int> res(a[0].size());
    iota(res.begin(), res.end(), 1);
    for(int i = 1; i < a.size(); ++ i){
        auto t = suffix_automaton(a[i]).process_lcs(a[0]);
        for(int j = 0; j < int(a[0].size()); ++ j) ctmin(res[j], t[j]);
    }
    int i = max_element(res.begin(), res.end()) - res.begin();
    return {a[0].begin() + i + 1 - res[i], a[0].begin() + i + 1};
}