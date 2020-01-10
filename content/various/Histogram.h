/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: me
 * Description: Maximum area of a histogram. 
 * Time: O(n)
 */

template<typename T = int>
T max_area(vector<int> v) {
    T ret = T();
    stack<int> s;
    v.insert(v.begin(), -1);
    v.insert(v.end(), -1);
    s.push(0);
    for(int i = 0; i < v.size(); ++i) {
        while (v[s.top()] > v[i]) {
            int h = v[s.top()]; s.pop();
            ret = max(ret, h * (i - s.top() - 1));
        }
        s.push(i);
    }
    return ret;
}
