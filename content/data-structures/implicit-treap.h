/**
 * Author: 
 * Date: 
 * Source: 
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 */

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct node {
	int v, p, sz;
	node *l, *r;
	bool rev;
	node(int k) : v(k), p(rng()), l(nullptr), rev(0), r(nullptr), sz(0) {}
};
int sz(node *t) {
	if (t == nullptr) return 0;
	return t->sz;
}
void push(node *t) {
	if (t == nullptr) return;
	if (t->rev) {
		swap(t->l, t->r);
		if (t->l != nullptr) t->l->rev ^= t->rev;
		if (t->r != nullptr) t->r->rev ^= t->rev;
		t->rev = 0;
	}
}
void updsz(node *t) {
	if (t == nullptr) return;
	push(t); push(t->l); push(t->r);
	t->sz = sz(t->l) + sz(t->r) + 1;
}
void split(node *t, node *&l, node *&r, int k) { //k on left
	push(t);
	if (t == nullptr) l = r = nullptr;
	else if (k <= sz(t->l)) {
		split(t->l, l, t->l, k);
		r = t;
	} 
	else {
		split(t->r, t->r, r, k-1-sz(t->l));
		l = t;
	}
	updsz(t);
}
void merge(node *&t, node *l, node *r) {
	push(l); push(r);
	if (l == nullptr) t = r;
	else if (r == nullptr) t = l;
	else if (l->p <= r->p) {
		merge(l->r, l->r, r);
		t = l;
	}
	else {
		merge(r->l, l, r->l);
		t = r;
	}
	updsz(t);
}
void add(node *&t, node *c, int k) {
	push(t);
	if (t == nullptr) t = c;
	else if (c->p >= t->p) {
		split(t, c->l, c->r, k);
		t = c;
	}
	else if (sz(t->l) >= k) add(t->l, c, k);
	else add(t->r, c, k-1-sz(t->l));
	updsz(t);
}
void del(node *&t, int k) {
	push(t);
	if (t == nullptr) return;
	if (sz(t->l) == k) merge(t, t->l, t->r);
	else if (sz(t->l) > k) del(t->l, k);
	else del(t->r, k);
	updsz(t);
}
void print(node *t) {
	if (r == nullptr) return;
	print(t->l);
	cout << t->v << ' ';
	print(t->r); 
}

int main() {
	node *treap = nullptr;
	while(1) {
		int a;
		cin >> a;
		if (a == 1) {
			int c, d;
			cin >> c >> d;
			node *r = new node(d);
			add(treap, r, c);
		} else if (a == 2) {
			int d;
			cin >> d;
			del(treap, d);
		} 
		print(treap);
	}
}
