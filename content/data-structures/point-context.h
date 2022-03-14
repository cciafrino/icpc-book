/**
* Author: Chris
* Description: Examples of Segment Tree
*/
struct seg_node {
	int val;
	int mi, ma;
	seg_node() : mi(INT_MAX), ma(INT_MIN), val(0) {}
	seg_node(int x) : mi(x), ma(x), val(x) {}
	void merge(const seg_node& l, const seg_node& r) {
	    val = l.val + r.val;
	    mi = min(l.mi, r.mi);
	    ma = max(l.ma, r.ma);
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
	bool go(int& acc, int& k) const {
	    if (val <= k) {
		k -= val;
		acc += val;
		return false;
	    } 
	    return true;
	}
};

// min of [a, N) <= x
auto find_min_right = [&](segtree<seg_node>& sg, int a, int x) -> int {
	int acc = INT_MAX;
	return sg.find_right(a, &seg_node::acc_min, acc, x);
};

// min of [0, a) <= x
auto find_min_left = [&](segtree<seg_node>& sg, int a, int x) -> int {
	int acc = INT_MAX;
	return sg.find_left(a, &seg_node::acc_min, acc, x);
};

// max of [a, N) >= x
auto find_max_right = [&](segtree<seg_node>& sg, int a, int x) -> int {
	int acc = INT_MIN;
	return sg.find_right(a, &seg_node::acc_max, acc, x);
};

// max of [0, a) >= x
auto find_max_left = [&](segtree<seg_node>& sg, int a, int x) -> int {
	int acc = INT_MIN;
	return sg.find_left(a, &seg_node::acc_max, acc, x);
};

// kth one of [a, N)
auto find_kth = [&](segtree<seg_node>& sg, int a, int x) -> int {
	int acc = 0;
	return sg.find_right(a, &seg_node::go, acc, x);
};
