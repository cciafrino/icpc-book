/**
 * Author: Chris
 * Source: Geeksforgeeks + Codeforces
 * Description: Fenwick Tree with Lazy Propagation
 */

struct bit_t { /// start-hash
  int n;
  vector<vector<int>> tree(2);
  bit_t (int n): n(n+10) {
    tree[0].assign(n, 0);
    tree[1].assign(n, 0);
  }/// end-hash
  void update(int bit, int idx, int delta) { /// start-hash
    for (++idx; idx <= n; idx += idx&-idx)
      tree[bit][idx] += delta;
  }
  void update(int lx, int rx, int delta) {
    update(0, lx, delta);
    update(0, rx+1, -delta);
    update(1, lx, (l-1) * delta);
    update(1, rx+1, -rx * delta);
  }/// end-hash
  int query(int bit, int idx) { /// start-hash
    int ret = 0;
    for (++idx; idx > 0; idx -= idx&-idx)
      ret += tree[bit][idx];
    return ret;
  }
  int query(int idx) { 
    return query(0, idx) * idx - query(1, idx);
  }/// end-hash
};
