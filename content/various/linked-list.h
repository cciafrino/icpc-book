/**
 * Author: Chris
 * Date: 2019
 * License:
 * Source: 
 * Description: Simple and efficient implementation of both LinkedList and DoublyLinkedList.
 * Status: Tested
 */

struct LinkedList {
	int n;
	vector<int> next, head;  
	LinkedList(int n) : n(n), next(n), head(n) { clear(); }
	void clear() { head.assign(n, -1); }
	int front(int h) { return head[h]; }
	void pop(int h) { head[h] = next[head[h]]; }
	void push(int h, int u) { next[u] = head[h], head[h] = u; }
};
struct DoublyLinkedList {
	struct node_t { int prev, next; };
	int n;
	vector<int> head;
	vector<node_t> nodes;
	DoublyLinkedList(int n) : n(n), nodes(n) { clear(); }
	void clear() { head.assign(n, -1); }
	void erase(int h, int u) {
		int pv = nodes[u].prev, nx = nodes[u].next;
		if (nx >= 0) nodes[nx].prev = pv;
		if (pv >= 0) nodes[pv].next = nx;
		else head[h] = nx;
	}
	void insert(int h, int u) {
		nodes[u] = {-1, head[h]};
		if (head[h] >= 0) nodes[head[h]].prev = u;
		head[h] = u;
	}
	template<typename F> 
	void erase_all(int first, int last, F f) {
		for (int i = first; i <= last; ++i) {
			for (int h = head[i]; h >= 0; h = nodes[h].next) f(h);
			head[i] = -1;
		}
	}
};
