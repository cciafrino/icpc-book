/**
 * Author: 
 * Date: 2017-10-31
 * License: CC0
 * Source: https://codeforces.com/contest/1181/submission/55632007
 * Description: Time and space efficient Segment Tree. Point update and range query.
 * Time: O(\log N)
 * Status: fuzz-tested
 */
struct Seg {
    vector<int> vals;
    int h = 1;
    Seg(int n) {
        while(h < n) h <<= 1;
        vals.resize(2*h, 0);
    }
    void activate(int i) {
        for (i += h; i > 0; i /= 2) vals[i] += 1;
    }
    int getKth(int k) {
        int i = 1;
        while(i < h) {
            i *= 2;
            if (vals[i] < k) {
                k -= vals[i];
                ++i;
            }
        }
        return i-h;
    }
};