#include<bits/stdc++.h>
using namespace std;

#include "../../content/data-structures/lichao-lazy.h"

using lint = int64_t;

template<typename data_t, data_t sz>
struct lichao_comp{
    static const data_t inf = numeric_limits<data_t>::max() / 2;

template<typename data_t1>
    struct Line {
        data_t1 a, b;
        Line() : a(0), b(-inf) {}
        Line(data_t1 a, data_t1 b) : a(a), b(b) {}

        data_t1 get(data_t1 x) {
            return a * x + b;
        }

        void add(Line x) {
            a += x.a;
            b += x.b;
        }
        };

    struct Node {
        Line<data_t> line = Line<data_t>();
        Line<data_t> lazy = Line<data_t>(0, 0);

        Node *lc = nullptr;
        Node *rc = nullptr;

        void apply(data_t l, data_t r, Line<data_t> v) {
            line.add(v);
            lazy.add(v);
        }
    };
    Node *root;
    lichao_comp():root(new Node){}

    void PushLazy(Node* &n, data_t tl, data_t tr) {
    if (n == nullptr) return;
    if (n->lc == nullptr) n->lc = new Node();
    if (n->rc == nullptr) n->rc = new Node();
    data_t mid = (tl + tr) / 2;
    n->lc->apply(tl, mid, n->lazy);
    n->rc->apply(mid + 1, tr, n->lazy);
    n->lazy = Line<data_t>(0, 0);
    }

    void PushLine(Node* &n, data_t tl, data_t tr) {
    if (n == nullptr) return;
    data_t mid = (tl + tr) / 2;
    InsertLineKnowingly(n->lc, tl, mid, n->line);
    InsertLineKnowingly(n->rc, mid + 1, tr, n->line);
    n->line = Line<data_t>();
    }

    void InsertLineKnowingly(Node* &n, data_t tl, data_t tr, Line<data_t> x) {
    if (n == nullptr) n = new Node();
    if (n->line.get(tl) < x.get(tl)) swap(n->line, x);
    if (n->line.get(tr) >= x.get(tr)) return;
    if (tl == tr) return;
    data_t mid = (tl + tr) / 2;
    PushLazy(n, tl, tr);
    if (n->line.get(mid) > x.get(mid)) {
        InsertLineKnowingly(n->rc, mid + 1, tr, x);
    } else {
        swap(n->line, x);
        InsertLineKnowingly(n->lc, tl, mid, x);
    }
    }

    void InsertLine(Node* &n, data_t tl, data_t tr, data_t l, data_t r, Line<data_t> x) {
    if (tr < l || r < tl || tl > tr || l > r) return;
    if (n == nullptr) n = new Node();
    if (l <= tl && tr <= r) return InsertLineKnowingly(n, tl, tr, x);
    data_t mid = (tl + tr) / 2;
    PushLazy(n, tl, tr);
    InsertLine(n->lc, tl, mid, l, r, x);
    InsertLine(n->rc, mid + 1, tr, l, r, x);
    }

    void AddLine(Node* &n, data_t tl, data_t tr, data_t l, data_t r, Line<data_t> x) {
    if (tr < l || r < tl || tl > tr || l > r) return;
    if (n == nullptr) n = new Node();
    if (l <= tl && tr <= r) return n->apply(tl, tr, x);
    data_t mid = (tl + tr) / 2;
    PushLazy(n, tl, tr);
    PushLine(n, tl, tr);
    AddLine(n->lc, tl, mid, l, r, x);
    AddLine(n->rc, mid + 1, tr, l, r, x);
    }

    data_t Query(Node* &n, data_t tl, data_t tr, data_t x) {
    if (n == nullptr) return -inf;
    if (tl == tr) return n->line.get(x);
    data_t res = n->line.get(x);
    data_t mid = (tl + tr) / 2;
    PushLazy(n, tl, tr);
    if (x <= mid) {
        res = max(res, Query(n->lc, tl, mid, x));
    } else {
        res = max(res, Query(n->rc, mid + 1, tr, x));
    }
    return res;
    }

    void InsertLine(data_t l, data_t r, Line<data_t> x) {
    return InsertLine(root, 0, sz - 1, l, r, x);
    }

    void AddLine(data_t l, data_t r, Line<data_t> x) {
    return AddLine(root, 0, sz - 1, l, r, x);
    }

    data_t Query(data_t x) {
        return Query(root, 0, sz - 1, x);
    }
};

int main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL); cout.tie(NULL);
    // const lint sz = int(2e5);
    // lichao_comp<lint, sz+1> lichao1;
    // lichao_lazy<lint, sz> lichao2;

    // int q;
    // q = 300000;
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_int_distribution<> distr(0, sz); 
    // while(q--){
    //     int ty = q%3;
    //     if(ty == 0){
    //         lint m = distr(gen), b=distr(gen), l=distr(gen), r=distr(gen);
    //         if(l > r) swap(l, r);
    //         lichao1.InsertLine(l, r, {m,b});
    //         lichao2.addSegment(m, b, l, r);
    //     } else if(ty == 1){
    //         lint m=distr(gen), b=distr(gen), l=distr(gen), r=distr(gen);
    //         if(l > r) swap(l, r);
    //         lichao1.AddLine(l, r, {m,b});
    //         lichao2.updateSegment(m, b, l, r);
    //     } else{
    //         int x=distr(gen);
    //         auto correct = lichao1.Query(x);
    //         auto mine = lichao2.query(x);
    //         assert( correct == mine);
    //     }
    // }
    
    // return 0;

    cout << "Skipped: need to be implemented!" << endl;
}