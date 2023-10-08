/**
 * Author: Chris
 * Description: Examples of Segment Tree
 */
struct seg_node { // bbfc07
	int val, int mi, ma;
	seg_node() : mi(INT_MAX), ma(INT_MIN), val(0) {}
	seg_node(int x) : mi(x), ma(x), val(x) {}
	void merge(const seg_node& l, const seg_node& r) {
		val = l.val + r.val;
		mi = min(l.mi, r.mi), ma = max(l.ma, r.ma);
	}
	void update(int x) {
		mi = ma = val = x;
	}
	bool acc_min(int& acc, int x) const {
		if (x >= mi) return true;
		if (acc > mi) acc = mi;
		return false;
	}
	bool acc_max(int& acc, int x) const {
		if (x <= ma) return true;
		if (acc < ma) acc = ma;
		return false;
	}
};
// 1 + min of [a, N) <= x
auto find_min_right = [&](segtree<seg_node>& sg, int a, int x) -> int {
	int acc = INT_MAX;
	return sg.find_first(a, N, &seg_node::acc_min, acc, x);
};
// max of [0, a) >= x
auto find_max_left = [&](segtree<seg_node>& sg, int a, int x) -> int {
	int acc = INT_MIN;
	return sg.find_last(0, a, &seg_node::acc_max, acc, x);
};
