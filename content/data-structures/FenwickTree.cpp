/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: TopCoder
 * Description: 
 * Time: Both operations are $O(\log N)$.
 */

struct bit_t {
    vector<int> tree;
    bit_t(int n){
        tree.assign(n, 0);
    }
    void update(int idx){
        while (idx < tree.size()){
            tree[idx]++;
            idx += idx & -idx;
        }
    }
    int query(int idx){
        int ret = 0;
        while (idx) {
            ret += tree[idx];
            idx -= idx & -idx;
        }
        return ret;
    }
};
