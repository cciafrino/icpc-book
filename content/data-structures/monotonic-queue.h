/**
 * Author: Chris
 * Date: 2021
 * License: Unknown
 * Description: Supports pop and push queue-like, and add function adds a constant to all elements currently in the queue.
 * Status: Tested
 * Time: $O(1)$
 */
template<typename T, typename Comp> struct monotonic_queue {
	int lo, hi; T S; ///start-hash
	deque<pair<T, T>> q;
	monotonic_queue() : lo(0), hi(0), S(0) {}
	void push(T val) {
		while(!q.empty() && Comp()(val, q.back().first + S))
			q.pop_back();
		q.emplace_back(val - S, hi++);
	}
	void pop() {
		if (!q.empty() && q.front().second == lo++) q.pop_front();
	} ///end-hash
	void add(T val) { S += val; }
	T get_val() const {  return q.front().first + S; }
	int size() const { return hi-lo; }
};
template<typename T> using min_queue = monotonic_queue<T, less_equal<T>>;
template<typename T> using max_queue = monotonic_queue<T, greater_equal<T>>;
