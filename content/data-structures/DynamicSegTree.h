/**
 * Author: Chris
 * Description: Dynamic Segment Tree with lazy propagation.
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
		if(v->l != nullptr){
			v->l->lazy += v->lazy;
			v->r->lazy += v->lazy;
		}
		v->lazy = 0;
	}
}
void update(node *v, int lx, int rx, lint val) {
	push(v);
	if(rx < v->lx) return;
	if(v->rx < lx) return;
	if(lx <= v->lx && v->rx <= rx) {
		v->lazy = val; 
		push(v);
		return;
	}
	update(v->l, lx, rx, val);
	update(v->r, lx, rx, val);	
	v->minv = min(v->l->minv, v->r->minv);
	v->sumv = v->l->sumv + v->r->sumv;	
}

lint mquery(node *v, int lx, int rx) {
	push(v);
	if(rx < v->lx) return 1e16;
	if(v->rx < lx) return 1e16;
	if(lx <= v->lx && v->rx <= rx) return v->minv;
	return min(mquery(v->l, lx, rx), mquery(v->r, lx, rx));
}

lint squery(node *v, int lx, int rx) {
	push(v);
	if(rx < v->lx) return 0;
	if(v->rx < lx) return 0;
	if(lx <= v->lx && v->rx <= rx) return v->sumv;
	return squery(v->l, lx, rx) + squery(v->r, lx, rx);
}

node *build(int lx, int rx) {
	node *v = new node();
	v->lx = lx; v->rx = rx;
	v->lazy = 0;
	if(lx == rx) 
		v->l = v->r = nullptr;
	else {
		v->l = build(lx, (lx + rx)/2);
		v->r = build((lx + rx)/2 + 1, rx);
		v->minv = min(v->l->minv, v->r->minv);
		v->sumv = v->l->sumv + v->r->sumv;
	}
	return v;
}

node *segtree = build(0, n);
