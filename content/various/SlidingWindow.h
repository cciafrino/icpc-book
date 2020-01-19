/**
 * Author: Chris
 * License: CC0
 * Description: Given an array $v$ and an integer $K$, the problem boils down to computing for each index $i: min(v[i], v[i-1], ..., v[i-K+1])$.
 * if $mx == true$, returns the maximum.
 * Status: tested
 * Time: $O(N)$
 */
 
vector<int> sliding_window_minmax(vector<int> &v, int K, bool mx) {
  deque<pair<int, int>> window;
  vector<int> ans;
  for (int i = 0; i < v.size(); i++) {
    if (mx) {
      while (!window.empty() && window.back().first <= v[i])
        window.pop_back();
    } else {
      while (!window.empty() && window.back().first >= v[i])
        window.pop_back();
    }
    window.emplace_back(v[i], i);
    while(window.front().second <= i - K)
      window.pop_front();
    ans.push_back(window.front().first);
  }
  return ans;
}
