/**
 * Author: ?
 * Description: 
 */

vector<vector<int>> m, w
vector<int> man_match;
void stable_marriage() {
    size_t M = m.size(), W = w.size();
    vector<int> woman_match(w, -1);
    man_match.assign(M, -1);
    vector<size_t> next_man(M, 0);
    stack<int> st;
    for (int i = 0; i < M; ++i) st.push(i);
    while(!st.empty()) {
        int x = st.top(); st.pop();
        if (man_match[x] != -1) continue;
        if (next_man[x] >= W) continue;
        int cur = m[x][next_man[x]++];
        if (woman_match[w] == -1) {
            man_match[x] = cur;
            woman_match[cur] = x;
        }
        else {
            int mp = woman_match[cur];
        }
    }
}
