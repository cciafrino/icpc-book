/**
 * Author: Chris 
 * Date: 
 * License: CC0
 * Source: 
 * Description: Build segment tree where each node stores a sorted version
        of the underlying range.
 * Status: fuzz-tested a bit
 * Time: $O(\log^2 N)$
 */

struct MergeSortTree {
    vector<int> v, id; 
    vector<vector<int>> tree;
    MergeSortTree(vector<int> &v) : v(v), tree(4*(v.size()+1)) {
        for(int i = 0; i < v.size(); ++i) id.push_back(i);
        sort(id.begin(), id.end(), [&v](int i, int j) { return v[i] < v[j]; });
        build(1, 0, v.size()-1);
    }
    void build(int id, int left, int right) {
        if (left == right) tree[id].push_back(id[left]);
        else {
            int mid = (left + right)>>1;
            build(id<<1, left, mid);
            build(id<<1|1, mid+1, right);
            tree[id] = vector<int>(right - left + 1);
            merge(tree[i<<1].begin(), tree[i<<1].end(), 
                tree[id<<1|1].begin(), tree[id<<1|1].end(), 
                tree[id].begin());   
        }
    }
    // how many elements in this node have id in the range [a,b]
    int how_many(int id, int a, int b) { 
        return (int)(upper_bound(tree[id].begin(), tree[id].end(), b)
            - lower_bound(tree[id].begin(), tree[id].end(), a));
    }
    int query(int id, int left, int right, int a, int b, int x) {
        if (left == right) return v[tree[id].back()];
        int mid = (left + right)>>1;
        int lcount = how_many(id<<1, a, b);
        if (lcount >= x) return query(id<<1, left, mid, a, b, x);
        else return query(id<<1|1, mid+1, right, a, b, x - lcount);
    }
    int kth(int a, int b, int k) { 
        return query(1, 0, v.size()-1, a, b, k);
    }
};