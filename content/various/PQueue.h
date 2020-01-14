/**
 * Author: Chris
 * License: CC0
 * Description: Efficient priority queue implementation. Initialize with highest possible value. Can obviously be extended to minheap/maxheap.
 * Status:
 * Time: 
 */

template<typename T>
struct PQ {
    int sz;
    vector<T> q;
    T offset=0;
    PQ(int n) : sz(n+1), q(2*n, -n) {}
    T top() { return -q[0]+offset; }
    void push(T x) {
        q[sz++]=-(x-offset);
        push_heap(q.begin(),q.begin()+sz);
    }
    void shift(T x) { offset+=x; }
    void pop() {
        pop_heap(q.begin(),q.begin()+sz); --sz;
    }
};