/**
 * Author: Chris
 * Description: Dynamic Segment Tree with lazy propagation. Allows range query, range update (increment and assignment). 
 * For assignment change all += to = in push and update functions. If not using lazy, remove all push related function calls.
 * License: CC0
 * Source: folklore
 * Time: $O(\lg(N))$
 * Status: Tested
 * Usage: vector<int> a;
 * node *segtree = build(0, n, a);
 */

struct node {
	node *l, *r;
	lint minv, sumv, lazy;
	int lx, rx;
};

void push(node *v) { 
	if(v != nullptr && v->lazy) { 
		v->minv += v->lazy;
		v->sumv += v->lazy * (v->rx - v->lx + 1);
		if(v->l) v->l->lazy += v->lazy;
		if(v->r) v->r->lazy += v->lazy;
		v->lazy = 0;
	}
}

void update(node *v, int lx, int rx, lint delta) {
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
	v->minv = min(v->l->minv, v->r->minv);
	v->sumv = v->l->sumv + v->r->sumv;	
}

// without propagation, way faster in practice
void upd(node *v, int lx, int rx, lint delta) {
	if(rx < v->lx || v->rx < lx) return;
	if(v->lx == v->rx) {
		v->lazy += delta; 
		v->minv += delta;
		v->sumv += delta;
		return;
	}
	upd(v->l, lx, rx, delta);
	upd(v->r, lx, rx, delta);	
	v->minv = max(v->l->minv, v->r->minv) + v->lazy;
	v->sumv = v->l->sumv + v->r->sumv + v->lazy * (v->rx - v->lx + 1);		
}

lint mquery(node *v, int lx, int rx) {
	push(v);
	if(rx < v->lx || v->rx < lx) return -1e16;
	if(lx <= v->lx && v->rx <= rx) return v->minv;
	return max(mquery(v->l, lx, rx), mquery(v->r, lx, rx));
}

lint squery(node *v, int lx, int rx) {
	push(v);
	if(rx < v->lx || v->rx < lx) return 0;
	if(lx <= v->lx && v->rx <= rx) return v->sumv;
	return squery(v->l, lx, rx) + squery(v->r, lx, rx);
}

node *build(int lx, int rx) {
	node *v = new node();
	v->lx = lx; v->rx = rx;
	if(lx == rx) {
		v->lazy = 0;
		v->l = v->r = nullptr;
		v->minv = v->sumv = 0;
	}
	else {
		v->l = build(lx, (lx + rx)/2);
		v->r = build((lx + rx)/2 + 1, rx);
		v->minv = min(v->l->minv, v->r->minv);
		v->sumv = v->l->sumv + v->r->sumv;
		v->lazy = 0;
	}
	return v;
}


