/**
 * Author: Tourist
 * License: CC0
 * Description: Compute the longest increasing subsequence.
 * Status: Not tested
 * Time: $O(N \log N)$
 */

template<typename T> int lis(const vector<T> &a) {
    vector<T> u;
    for (const T &x : a) {
        auto it = lower_bound(u.begin(), u.end(), x);
        if (it == u.end()) u.push_back(x);
        else *it = x;
    }
    return (int)u.size();
}
