/**
 * Author: Andre Sousa
 * Date: 2019-04-11
 * License: Unknown
 * Description: Structure that supports all operations of a queue and get the minimum/maximum active value in the queue. Useful for sliding window 1D and 2D. For 2D problems, you will need to pre-compute another matrix, by making a row-wise traversal, and calculating the min/max value beginning in each cell. Then you just make a column-wise traverse as they were each an independent array.
 * Status: fuzz-tested
 * Time: $O(1)$ 
 */

template<typename T> 
struct minQueue {
	int lx, rx, sum;
	deque<pair<T, T>> q;
	minQueue() { lx = 1; rx = 0; sum = 0; }
	void clear() { lx = 1, rx = 0, sum = 0; q.clear(); }
	void push(T delta) {
	   // q.back().first + sum <= delta for a maxQueue
		while(!q.empty() && q.back().first + sum >= delta)
			q.pop_back();
		q.emplace_back(delta - sum, ++rx);
	}
	void pop() {
		if (!q.empty() && q.front().second == lx++)
			q.pop_front();
	}
	void add(T delta) { 
		sum += delta; 
	}
	T getMin() {
		return q.front().first + sum;
	}
	int size() { return rx-lx+1; }
};
