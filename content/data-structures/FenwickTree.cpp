/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: TopCoder
 * Description: 
 * Time: Both operations are $O(\log N)$.
 */

template<typename T> struct bit_t {
    vector<T> tree;
    bit_t(int n){
        tree.assign(n, T());
    }
    void update(int idx){
        while (idx < tree.size()){
            tree[idx]++;
            idx += idx & -idx;
        }
    }
    T query(int idx){
        T ret = 0;
        while (idx) {
            ret += tree[idx];
            idx -= idx & -idx;
        }
        return ret;
    }
};
