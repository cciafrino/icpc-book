/**
 * Author: Chris
 * Date: 2021
 * License: Unknown
 * Description: Structure that supports all operations of a queue and get the minimum/maximum active value in the queue. Useful for sliding window 1D and 2D. For 2D problems, you will need to pre-compute another matrix, by making a row-wise traversal, and calculating the min/max value beginning in each cell. Then you just make a column-wise traverse as they were each an independent array.
 * Status: Tested
 * Time: $O(1)$ 
 */
template <typename T, typename Comp> struct monotonic_queue {
	vector<pair<T, int>> q;
	int lo, hi;
	monotonic_queue(int max_sz) : q(max_sz), lo(0), hi(0) {}
	size_t size() const { return hi - lo + 1; }
	void push(T val, int idx) {
		while (hi > lo && Comp()(val, q[hi-1].first)) --hi;
		q[hi++] = {val, idx};
	}
	void pop(int idx) {
		if (lo < hi && q[lo].second == idx) lo++;
	}
	T get_val() const {
		assert(lo < hi);
		return q[lo].first;
	}
};
template<typename T> using min_monotonic_queue = monotonic_queue<T, std::less<T>>;
template<typename T> using max_monotonic_queue = monotonic_queue<T, std::greater<T>>;
