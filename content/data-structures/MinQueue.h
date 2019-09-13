/**
 * Author: Andre Sousa
 * Date: 2019-04-11
 * License: Unknown
 * Description:
 * Status: fuzz-tested
 */

template<typename T> struct minQueue {
	T lx, rx, sum;
	deque<pair<T, T>> q;
	minQueue() { lx = 1; rx = 0; sum = 0; }
	void clear() { lx = 1, rx = 0, sum = 0; q.clear(); }
	void push(T delta) {
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
	int size() { return rx-lx; }
};
