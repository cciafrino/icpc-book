/**
 * Author: Chris
 * Date: 
 * License: CC0 
 * Source: 
 * Description: Segment Tree with Lazy update (half-open interval). 
 * Status: 
 * Time: $O(\lg(N)*Q)$
 */

template<class T> struct segtree_range {
  int H, N;
  vector<T> ts;
  segtree_range() {}
  explicit segtree_range(int N_) {
    for (H = 0, N = 1; N < N_; ++H, N *= 2) {}
    ts.resize(2*N);
    build();
  }
  template<class Q> explicit segtree_range(const vector<Q>& qs) {
    const int N_ = int(qs.size());
    for (H = 0, N = 1; N < N_; ++H, N *= 2) {}
    ts.resize(2*N);
    for (int i = 0; i < N_; ++i) at(i) = T(qs[i]);
    build();
  }
  T& at(int a) { return ts[a + N]; }
  void build() { for (int a = N; --a; ) merge(a); }
  inline void push(int a) { ts[a].push(ts[2 * a], ts[2 * a + 1]); }
  inline void merge(int a) { ts[a].merge(ts[2*a], ts[2*a+1]); }
  // f0fcbd
  void for_parents_down(int a, int b) {
    for (int h = H; h; --h) {
      const int l = (a >> h), r = (b >> h);
      if (l == r) {
        if ((l << h) != a || (r << h) != b) push(l);
      } else {
        if ((l << h) != a) push(l);
        if ((r << h) != b) push(r);
      }
    }
  }
  // a25cb
  void for_parents_up(int a, int b) {
    for (int h = 1; h <= H; ++h) {
      const int l = (a >> h), r = (b >> h);
      if (l == r) {
        if ((l << h) != a || (r << h) != b) merge(l);
      } else {
        if ((l << h) != a) merge(l);
        if ((r << h) != b) merge(r);
      }
    }
  }
  // 6014b
  template<class F, class... Args> void update(int a, int b, F f, Args&&... args) {
    if (a == b) return;
    a += N; b += N;
    for_parents_down(a, b);
    for (int l = a, r = b; l < r; l /= 2, r /= 2) {
      if (l & 1) (ts[l++].*f)(args...);
      if (r & 1) (ts[--r].*f)(args...);
    }
    for_parents_up(a, b);
  }
  T query(int a, int b) {
    if (a == b) return T();
    a += N; b += N;
    for_parents_down(a, b);
    T lhs, rhs, t;
    for (int l = a, r = b; l < r; l /= 2, r /= 2) {
      if (l & 1) { t.merge(lhs, ts[l++]); lhs = t; }
      if (r & 1) { t.merge(ts[--r], rhs); rhs = t; }
    }
    t.merge(lhs, rhs); return t;
  }
  // 5a862
  template<class Op, class E, class F, class... Args> 
    auto query(int a, int b, Op op, E e, F f, Args&&... args) {
      if (a == b) return e();
      a += N; b += N;
      for_parents_down(a, b);
      auto lhs = e(), rhs = e();
      for (int l = a, r = b; l < r; l /= 2, r /= 2) {
        if (l & 1) { lhs = op(lhs, (ts[l++].*f)(args...)); };
        if (r & 1) { rhs = op((ts[--r].*f)(args...), rhs); };
      }
      return op(lhs, rhs);
    }
  // aab16
  // find min i s.t. T::f(args...) returns true in [a, i) from left to right
  template<class F, class... Args> int find_right(int a, F f, Args &&... args) {
    assert(0 <= a && a <= N);
    if ((T().*f)(args...)) return a;
    if (a == N) return 1 + N;
    a += N;
    for (int h = H; h; --h) push(a >> h);
    for (; ; a /= 2) if (a & 1) {
      if ((ts[a].*f)(args...)) {
        for (; a < N; ) {
          push(a);
          if (!(ts[a <<= 1].*f)(args...)) ++a;
        }
        return a - N + 1;
      }
      ++a;
      if (!(a & (a - 1))) return N + 1;
    }
  } 
  // a033b
  // find max i s.t. T::f(args...) returns true in [i, a) from right to left
  template<class F, class... Args> int find_left(int a, F f, Args &&... args) {
    assert(0 <= a && a <= N);
    if ((T().*f)(args...)) return a;
    if (a == 0) return -1;
    a += N;
    for (int h = H; h; --h) push((a - 1) >> h);
    for (; ; a /= 2) if ((a & 1) || a == 2) {
      if ((ts[a - 1].*f)(args...)) {
        for (; a <= N; ) {
          push(a - 1);
          if (!(ts[(a <<= 1) - 1].*f)(args...)) --a;
        }
        return a - N - 1;
      }
      --a;
      if (!(a & (a - 1))) return -1;
    }
  }
};
