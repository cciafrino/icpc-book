/**
 * Author: LeticiaFCS
 * Source: radoslav11, https://codeforces.com/blog/entry/86731
 * Description: Line Segments Li Chao Tree. Allows line add, segment add and point query. Set the start index of each leaf!
 * Status: Tested on yosupo
 * Time: $O(\log N)$ except for segment add $O(\log^2 N)$
 */
 #include "rec-lazy-segtree.h" // add:
template<class F, class... Args> void find_node(int v, int l, int r, F f, Args&&... args) { //in segtree_range!!!
    int child = (ts[v].*f)(args...);
    int m = (l + r) / 2;	
    if(child == -1) find_node(2*v, l, m, f, args...);
    else if(child == 1) find_node(2*v+1, m, r, f, args...);
}
template<class T> struct seg_node {
    static const T inf = numeric_limits<T>::max();
    int l, sz, id;
    T a, b;
    seg_node(int left = 0, int s = 1, int i = -1, T xa = 0, T xb = inf) : l(left), sz(s) , id(i), a(xa), b(xb) {}
    T get(int x){ return values[ min<int>(x, values.size() - 1) ]; }
    T apply(int x){
        return ((b == inf) ? inf : a * get(x) + b);
    } 
    void merge(const seg_node& left, const seg_node& right) {
        l = min(left.l, right.l);
        sz = left.sz + right.sz;
    }
    int add_line(seg_node &new_line) {
        int r = l + sz;
        int mid = (l + r) / 2;
        if(apply(mid) > new_line.apply(mid)){
            swap(id, new_line.id);
            swap(a, new_line.a);
            swap(b, new_line.b);
        }
        if(apply(l) > new_line.apply(l)) return -1;
        if(apply(r-1) > new_line.apply(r-1)) return 1;
        return 0;
    }
    int query(int x, pair<T,int> &ans){
        ans = min(ans, make_pair(apply(x), id));
        if(sz == 1) return 0;
        int mid = (l + l+sz) / 2;
        if(x < mid) return -1;
        return 1;        
    }
    void add_segment(vector<pair<int, int>> &important){ 
        important.emplace_back(l, sz);
    }
};
auto query = [&](int x) {
    auto ans = make_pair(seg_node<int64_t>::inf, -1);
    sg.find_node(&seg_node<int64_t>::query, x, ans);
    return ans;
};
auto add_segment = [&](int64_t a, int64_t b, int l, int r, int line_id = -1) {
    vector<pair<int, int>> important;
    sg.update(l, r, &seg_node<int64_t>::add_segment, important);
    for(const auto &[l, sz] : important){
        int64_t av = a, bv = b;
        sg.find_node(sg.N/sz + l/sz, l, l + sz, &seg_node<int64_t>::add_line, seg_node<int64_t>(0, 1, line_id, av, bv));
    }
};