/**
 * Author: BenQ
 * Date: 
 * License: CC0
 * Source: 
 * Description: Sweep line algorithm that calculates area of union of rectangles in the form [x1,x2) x [y1,y2)
 * Usage: Create vector with both x's coordinates and y's coordinates of each rectangle.//vector<pair<int,int>,pair<int,int>> rectangles;// rectangles.push_back({{x1, x2}, {y1, y2}});// lint result = rectangle_union_area(rectangles);
 * Status: tested
 */

pair<int,int> operator+(const pair<int,int>& l, const pair<int,int>& r) {
    if (l.first != r.first) return min(l,r);
    return {l.first, l.second + r.second};
}
 
struct segtree_t { // stores min + # of mins
    int n;
    vector<int> lazy;
    vector<pair<int,int>> tree; // set n to a power of two
    segtree_t(int _n) : n(_n), tree(2*n, {0,0}), lazy(2*n, 0) { }
    void build() {
        for(int i = n-1; i >= 1; --i) 
            tree[i] = tree[i<<1] + tree[i<<1|1]; }
    void push(int v, int lx, int rx) {
        tree[v].first += lazy[v];
        if (lx != rx) {
            lazy[v<<1] += lazy[v];
            lazy[v<<1|1] += lazy[v];
        }
        lazy[v] = 0;
    }
    void update(int a, int b, int delta) { update(1,0,n-1,a,b,delta); }
    void update(int v, int lx, int rx, int a, int b, int delta) {
        push(v, lx, rx);
        if (b < lx || rx < a) return;
        if (a <= lx && rx <= b) {
            lazy[v] = delta; push(v, lx, rx);
        }
        else {
            int m = lx + (rx - lx)/2;
            update(v<<1, lx, m, a, b, delta);
            update(v<<1|1, m+1, rx, a, b, delta);
            tree[v] = (tree[v<<1] + tree[v<<1|1]);
        }
    }
};
 
lint rectangle_union_area(vector<pair<pair<int,int>,pair<int,int>>> v) { // area of union of rectangles
    const int n = 1<<18;
    segtree_t tree(n);
    vector<int> y; for(auto &t : v) y.push_back(t.second.first), y.push_back(t.second.second);
    sort(y.begin(), y.end()); y.erase(unique(y.begin(), y.end()),y.end());
    for(int i = 0; i < y.size()-1; ++i) tree.tree[n+i].second = y[i+1]-y[i]; // compress coordinates
    tree.build();
    vector<array<int,4>> ev; // sweep line
    for(auto &t : v) {
        t.second.first = lower_bound(y.begin(), y.end(),t.second.first)-begin(y);
        t.second.second = lower_bound(y.begin(), y.end(),t.second.second)-begin(y)-1;
        ev.push_back({t.first.first,1,t.second.first,t.second.second});
        ev.push_back({t.first.second,-1,t.second.first,t.second.second});
    }
    sort(ev.begin(), ev.end());
    lint ans = 0;
    for(int i = 0; i < ev.size()-1; ++i) {
        const auto& t = ev[i];
        tree.update(t[2],t[3],t[1]);
        int len = y.back()-y.front()-tree.tree[1].second; // tree.mn[0].firstshould equal 0
        ans += (lint)(ev[i+1][0]-t[0])*len;
    }
    return ans;
}
