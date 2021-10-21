/**
 * Author: Chris
 * Date: 
 * License: CC0 
 * Source: 
 * Description: Segment Tree with Lazy update (half-open interval). 
 * T, NZ := monoid
 * F := T * T -> T
 * US := NZ * T * int -> T 
 * UY := NZ * NZ -> NZ
 * Status: 
 * Time: $O(\lg(N)*Q)$
 */
template<class F, class US, class UY, class NZ, class T>
struct segtree_lz {
  const F f;
  const US s;
  const UY y;
  const NZ id_z;
  const T id_t;
  int N;
  vector<T> tree;
  vector<NZ> lazy;
  segtree_lz(int n, const F ff, const US ss, const UY yy, const NZ& idz={}, const T& idt={}) :
    f(ff), s(ss), y(yy), id_z(idz), id_t(idt) {
    for (N = 1; N < n; N *= 2) {}
    tree.assign(2 * N, id_t);
    lazy.assign(2 * N, id_z);
  }
  T& at(int a){ return tree[N + a]; }
  void build() {
    for (int a = N; --a; )
      tree[a] = f(tree[2 * a], tree[2 * a + 1]);
  }
  T query(int a, int b, const NZ& x) {
    return query(1, 0, N, a, b, x);
  }
  T query(int v, int l, int r, int a, int b, const NZ& x) { //(A)
    if (a < l) a = l; // (B)
    if (b > r) b = r; // (C)
    if (a >= b) return id_t;
    if (a == l && b == r) {
      //if (x != id_t) // (D)
      {
      	tree[v] = s(x, tree[v], r - l); // (E)
      	lazy[v] = y(x, lazy[v]); // (F)
      }
      return tree[v];
    }
    const int vL = 2 * v, vR = 2 * v + 1;
    const int md = (l + r) / 2;
    //if (lazy[v] != id_z) // (G)
    {
      tree[vL] = s(lazy[v], tree[vL], md - l); // (H)
      tree[vR] = s(lazy[v], tree[vR], r - md); // (I)
      lazy[vL] = y(lazy[v], lazy[vL]); // (J)
      lazy[vR] = y(lazy[v], lazy[vR]); // (K)
      lazy[v] = id_z;
    }
    const T lhs = query(vL, l, md, a, b, x);
    const T rhs = query(vR, md, r, a, b, x);
    tree[v] = f(tree[vL], tree[vR]); // (L)
    return f(lhs, rhs); //(M)
  }
};
