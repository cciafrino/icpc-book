/**
 * Author: BenQ
 * Description: Sparse Segment Tree with point update. Doesnt allocate storage for nodes with no data. Use BumpAllocator for better performance!
 * Time: 
 */
const int SZ = 1<<19;
template<class T> struct node_t {
	T delta = 0; node_t<T>* c[2];
	node_t() { c[0] = c[1] = nullptr; }
	void upd(int pos, T v, int L = 0, int R = SZ-1) { // add v
		if (L == pos && R == pos) { delta += v; return; }
		int M = (L + R)>>1;
		if (pos <= M) {
			if (!c[0]) c[0] = new node_t();
			c[0]->upd(pos, v, L, M);
		} else {
			if (!c[1]) c[1] = new node_t();
			c[1]->upd(pos, v, M+1, R);
		}
		delta = 0; 
		for (int i = 0; i < 2; ++i) if (c[i]) delta += c[i]->delta;
	}
	T query(int lx, int rx, int L = 0, int R = SZ-1) { // query sum of segment
		if (rx < L || R < lx) return 0;
		if (lx <= L && R <= rx) return delta;
		int M = (L + R)>>1; T res = 0;
		if (c[0]) res += c[0]->query(lx, rx, L, M);
		if (c[1]) res += c[1]->query(lx, rx, M+1, R);
		return res;
	}
	void upd(int pos, node_t *a, node_t *b, int L = 0, int R = SZ-1) {
		if (L != R) {
			int M = (L + R)>>1;
			if (pos <= M) {
				if (!c[0]) c[0] = new node_t();
				c[0]->upd(pos, a ? a->c[0] : nullptr, b ? b->c[0] : nullptr, L, M);
			} else {
				if (!c[1]) c[1] = new node_t();
				c[1]->upd(pos,a ? a->c[1] : nullptr, b ? b->c[1] : nullptr, M+1, R);
			}
		} 
		delta = (a ? a->delta : 0)+(b ? b->delta : 0);
	}
};