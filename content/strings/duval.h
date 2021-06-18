/**
 * Author: Tourist
 * Source: 
 * Description: A string is called simple (or a Lyndon word), if it is strictly smaller than any of its own nontrivial suffixes.
 * Time: O(N)
 * Status: Fuzz-tested
 * Usage:
 */
template <typename T>
pair<int, vector<string>> duval(int n, const T &s) { /// start-hash
    assert(n >= 1);
    // s += s  //uncomment if you need to know the min cyclic string
    vector<string> factors; // strings here are simple and in non-inc order
    int i = 0, ans = 0;
    while (i < n) { // until n/2 to find min cyclic string
        ans = i;
        int j = i + 1, k = i;
        while (j < n + n && !(s[j % n] < s[k % n])) {
            if (s[k % n] < s[j % n]) k = i;
            else k++;
            j++;
        }
        while (i <= k) {
            factors.push_back(s.substr(i, j-k));
            i += j - k;
        }
    }
    return {ans, factors};
    // returns 0-indexed position of the least cyclic shift
    // min cyclic string will be s.substr(ans, n/2)
} /// end-hash
template <typename T>
pair<int, vector<string>> duval(const T &s) {
    return duval((int) s.size(), s);
}
