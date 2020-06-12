/**
 * Author: Chris
 * Description: Dynamic Segment Tree with lazy propagation. Allows range query, range update (increment and assignment). 
 * For assignment change all += to = in push and update functions. If not using lazy, remove all push related function calls.
 * License: CC0
 * Source: folklore
 * Time: $O(\lg(N))$
 * Status: Tested
 * Usage: node *segtree = build(0, n);
 */

struct node {
	node *l, *r;
	int maxv, sumv, lazy;
	int lx, rx;
};
void push(node *v) { 
	if(v != nullptr && v->lazy) { 
		v->maxv += v->lazy;
		v->sumv += v->lazy * (v->rx - v->lx + 1);
		if(v->l) v->l->lazy += v->lazy;
		if(v->r) v->r->lazy += v->lazy;
		v->lazy = 0;
	}
}
void update(node *v, int lx, int rx, int delta) {
	push(v);
	if(rx < v->lx || v->rx < lx) return;
	if(lx <= v->lx && v->rx <= rx) {
		v->lazy += delta; 
		push(v);
		return;
	}
	update(v->l, lx, rx, delta);
	update(v->r, lx, rx, delta);	
	push(v->l);
	v->maxv = max(v->l->maxv, v->r->maxv);
	v->sumv = v->l->sumv + v->r->sumv;	
}
int mquery(node *v, int lx, int rx) {
	push(v);
	if(rx < v->lx || v->rx < lx) return -1;
	if(lx <= v->lx && v->rx <= rx) return v->maxv;
	return max(mquery(v->l, lx, rx), mquery(v->r, lx, rx));
}
int squery(node *v, int lx, int rx) {
	push(v);
	if(rx < v->lx || v->rx < lx) return 0;
	if(lx <= v->lx && v->rx <= rx) return v->sumv;
	return squery(v->l, lx, rx) + squery(v->r, lx, rx);
}
int find_first(node *v, int lx, int rx, int delta) { // st pos >= delta
	if (rx < v->lx || v->rx < lx || v->maxv < delta) return -1;
	if (v->lx == v->rx) return v->lx;
	int x = find_first(v->l, lx, rx, delta);
	if (x != -1) return x;
	return find_first(v->r, lx, rx, delta);
}
int find_last(node *v, int lx, int rx, int delta) { // last pos >= delta
	if (rx < v->lx || v->rx < lx || v->maxv < delta) return -1;
	if (lx == rx) return lx;
	int x = find_last(v->r, lx, rx, delta);
	if (x != -1) return x;
	return find_last(v->l, lx, rx, delta);
}
node *build(int lx, int rx) {
	node *v = new node();
	v->lx = lx; v->rx = rx;
	if(lx == rx) {
		v->lazy = 0;
		v->l = v->r = nullptr;
		v->maxv = v->sumv = 0;
	}
	else {
		v->l = build(lx, (lx + rx)/2);
		v->r = build((lx + rx)/2 + 1, rx);
		v->maxv = max(v->l->maxv, v->r->maxv);
		v->sumv = v->l->sumv + v->r->sumv;
		v->lazy = 0;
	}
	return v;
}


