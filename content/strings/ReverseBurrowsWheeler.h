/**
 * Author: BenQ
 * Description: Reverse of Burrows-Wheeler 
 * Time: $O(nlog(n))
 */

string RBW(string &s) {
    vector<pair<char,int>> v;
    vector<int> nex(s.size());
    for (int i = 0; i < s.size(); ++i) 
        v.push_back({s[i], i});
    sort(v.begin(), v.end());
    for (int i = 0; i < s.size(); ++i)
        nex[i] = v[i].second;
    int cur = nex[0];
    string result;
    while(cur) {
        result += v[cur].first;
        cur = nex[cur];
    }
    return result;
}
