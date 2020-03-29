/**
 * Author: Chris
 * Date: 2020
 * License: CC0
 * Source: tfg
 * Description: 2D Segment Tree. 
 * Status: Tested on URI 1511 & 2656
 */
#include "SparseSegtree.h"
template<class T> struct Node {
    node_t<T> seg; Node* c[2];
    Node() { c[0] = c[1] = nullptr; }
    void upd(int x, int y, T v, int L = 0, int R = SZ-1) { // add v
        if (L == x && R == x) { seg.upd(y,v); return; }
        int M = (L+R)>>1;
        if (x <= M) {
            if (!c[0]) c[0] = new Node();
            c[0]->upd(x,y,v,L,M);
        } else {
            if (!c[1]) c[1] = new Node();
            c[1]->upd(x,y,v,M+1,R);
        }
        seg.upd(y,v); // only for addition
        // seg.upd(y,c[0]?&c[0]->seg:nullptr,c[1]?&c[1]->seg:nullptr);
    }
    T query(int x1, int x2, int y1, int y2, int L = 0, int R = SZ-1) { // query sum of rectangle
        if (x1 <= L && R <= x2) return seg.query(y1,y2);
        if (x2 < L || R < x1) return 0;
        int M = (L+R)>>1; T res = 0;
        if (c[0]) res += c[0]->query(x1, x2, y1, y2, L, M);
        if (c[1]) res += c[1]->query(x1, x2, y1, y2, M+1, R);
        return res;
    }
};