/**
 * Author: 
 * Date: 
 * Source: 
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 */
struct node { ///start-hash
	int val, p, sz; bool rev;
	array<node*, 2> c{nullptr, nullptr};
	node(int k) : val(k), p(rng()), sz(0), rev(false) {}
	~node() {
		delete c[0];
		delete c[1];
	}
};///end-hash
inline int sz(node *t) {///start-hash
	return (!t ? 0 : t->sz);
}///end-hash
inline void push(node *t) {///start-hash
	if (!t) return;
	if (t->rev) {
		swap(t->c[0], t->c[1]);
		if (t->c[0]) t->c[0]->rev ^= t->rev;
		if (t->c[1]) t->c[1]->rev ^= t->rev;
		t->rev = 0;
	}
}///end-hash
inline void pull(node *t) {///start-hash
	if (!t) return;
	push(t); push(t->c[0]); push(t->c[1]);
	t->sz = sz(t->c[0]) + sz(t->c[1]) + 1;
}///end-hash
inline void split(node *t, node *&a, node *&b, int k) { //k on left
	push(t);
	if (!t) a = b = nullptr;
	else if (k <= sz(t->c[0])) {
		split(t->c[0], a, t->c[0], k);
		b = t;
	} else {
		split(t->c[1], t->c[1], b, k-1-sz(t->c[0]));
		a = t;
	}
	pull(t);
}
inline void merge(node *&t, node *a, node *b) {///start-hash
	push(a); push(b);
	if (!a) t = b;
	else if (!b) t = a;
	else if (a->p <= b->p) {
		merge(a->c[1], a->c[1], b);
		t = a;
	} else {
		merge(b->c[0], a, b->c[0]);
		t = b;
	}
	pull(t);
}///end-hash
inline void add(node *&t, node *a, int k) {///start-hash
	push(t);
	if (!t) t = a;
	else if (a->p >= t->p) {
		split(t, a->c[0], a->c[1], k);
		t = a;
	} else if (sz(t->c[0]) >= k) add(t->c[0], a, k);
	else add(t->c[1], a, k-1-sz(t->c[0]));
	pull(t);
}///end-hash
void del(node *&t, int k) {///start-hash
	push(t);
	if (!t) return;
	if (sz(t->c[0]) == k) merge(t, t->c[0], t->c[1]);
	else if (sz(t->c[0]) > k) del(t->c[0], k);
	else del(t->c[1], k);
	pull(t);
}///end-hash
inline void dump_treap(node *t) {///start-hash
	if (!t) return;
	push(t);
	dump_treap(t->c[0]);
	cerr << t->val << ' ';
	dump_treap(t->c[1]);
}///end-hash
