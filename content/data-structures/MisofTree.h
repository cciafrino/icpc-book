/**
 * Author: Chris
 * Description: A simple treedata structure for inserting, erasing, and querying the $n^{th}$ largest element.
 * Time: $O(\alpha(N))$
 */

const int BITS = 15;
struct misof_tree{
    int cnt[BITS][1<<BITS];
    misof_tree() {memset(cnt, 0, sizeof cnt);}
    void add(int x, int dv) {
        for (int i = 0; i < BITS; cnt[i++][x] += dv, x >>= 1); }
    void del(int x, int dv) {
        for (int i = 0; i < BITS; cnt[i++][x] -= dv, x >>= 1); }
    int nth(int n) {
        int r = 0, i = BITS;
        while(i--) if (cnt[i][r <<= 1] <= n)
            n -= cnt[i][r], r |= 1;
        return r;
    }
};
