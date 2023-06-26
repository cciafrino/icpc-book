/**
 * Author: someone on Codeforces
 * Date: 
 * Source: 
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 */
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct node {
	int k, p, sz;
	node *l, *r;
	node(int k) : k(k), p(rng()), l(nullptr), r(nullptr), sz(0) {}
};

int sz(node *t) {
	if (t == nullptr) return 0;
	return t->sz;
}

void updsz(node *t) {
	if (t == nullptr) return;
	t->sz = sz(t->l) + sz(t->r) + 1;
}
void split(node *t, node *&l, node *&r, int k) {
	if (t == nullptr) l = r = nullptr;
	else if (k <= t->k) {
		split(t->l, l, t->l, k);
		r = t;
	} 
	else {
		split(t->r, t->r, r, k);
		l = t;
	}
	updsz(t);
}
void merge(node *&t, node *l, node *r) {
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
void add(node *&t, node *c) {
	if (t == nullptr) t = c;
	else if (c->p >= t->p) {
		split(t, c->l, c->r, c->k);
		t = c;
	}
	else if (c->k <= t->k) add(t->l, c);
	else add(t->r, c);
	updsz(t);
}
void del(int k, node *&t) {
	if (t->k == k) merge(t, t->l, t->r);
	else if (t->k > k) del(k, t->l);
	else del(k, t->r);
	updsz(t);
}
node *find(node *t, int k) {
	if (t == nullptr) return t;
	if (t->k == k) return t;
	if (t->k < k) return find(t->r, k);
	else return find(t->l, k);
}
int cnt(node *t, int k) { // <= k
	if (t == nullptr) return 0;
	if (t->k <= k) return 1 + sz(t->l) + cnt(t->r, k);
	else cnt(t->l, k);
}
void print(node *r) {
	if (r == nullptr) return;
	cout << r->k << ' ' << r->p << ' ' << r->sz << '\n';
	print(r->l);  print(r->r);
}
node *kth(node *t, int k) {
	if (k == sz(t->l)) return t;
	else if (k < sz(t->l)) return kth(t->l, k);
	else return kth(t->r, k-1-sz(t->l));
}

int main() {
	node *treap = nullptr;
	while(1) {
		int a;
		cin >> a;
		if (a == 1) {
			int c;
			cin >> c;
			node *r = new node(c);
			add(treap, r);
			print(treap);
		} else if (a == 2) {
			int d;
			cin >> d;
			del(d, treap);
			print(treap);
		} else if (a == 3) {
			for (int i = 0; i < sz(treap); ++i) 
				cout << kth(treap, i)->k << '\n';
		}
	}
}
