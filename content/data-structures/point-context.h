/**
 * Author: Chris
 * Description: Examples of Segment Tree
 */
struct seg_node { 
	int val, int mi, ma;
	seg_node() : mi(INT_MAX), ma(INT_MIN), val(0) {}
	seg_node(int x) : mi(x), ma(x), val(x) {}
	void merge(const seg_node& l, const seg_node& r) {
		val = l.val + r.val;
		mi = min(l.mi, r.mi), ma = max(l.ma, r.ma);
	}
	void update(int x) { mi = ma = val = x; }
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