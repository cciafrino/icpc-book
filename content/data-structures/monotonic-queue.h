/**
 * Author: Chris
 * Date: 2021
 * License: Unknown
 * Description: Structure that supports all operations of a queue and get the minimum/maximum active value in the queue. Useful for sliding window 1D and 2D. For 2D problems, you will need to pre-compute another matrix, by making a row-wise traversal, and calculating the min/max value beginning in each cell. Then you just make a column-wise traverse as they were each an independent array.
 * Status: Tested
 * Time: $O(1)$ 
 */
template<typename T, T (*op)(const T&, const T&)> struct monotonic_queue {
    vector<T> as, aas;
    vector<T> bs, bbs;
    void reserve(int N) {
        as.reserve(N); aas.reserve(N);
        bs.reserve(N); bbs.reserve(N);
    }
    void reduce() {
        while (!bs.empty()) {
            as.push_back(bs.back());
            aas.push_back(aas.empty() ? bs.back() : op(bs.back(), aas.back()));
            bs.pop_back(); bbs.pop_back();
        }
    }
    T get() {
        if (as.empty()) reduce();
        return (bbs.empty() ? aas.back() : op(aas.back(), bbs.back()));
    }
    bool empty() const { return (as.empty() && bs.empty()); }
    int size() const { return int(as.size()) + int(bs.size()); }
    T front() {
        if (as.empty()) reduce();
        return as.back();
    }
    void push(const T& val) {
        bs.push_back(val);
        bbs.push_back(bbs.empty() ? val : op(bbs.back(), val));
    }
    void pop() {
        if (as.empty()) reduce();
        as.pop_back();
        aas.pop_back();
    }
};

// min/max
template<typename T> T mapping_min(const T& a, const T& b) {
	return min(a, b);
}
template<typename T> using min_monotonic_queue = monotonic_queue<T, mapping_min>;
// gcd 
template<typename T> T mapping_gcd(const T& a, const T& b) {
	return __gcd(a, b);
}
template<typename T> using gcd_monotonic_queue = monotonic_queue<T, mapping_gcd>;

// affine function
template<typename T> struct affine_t {
	T b, c;
};
template<typename T> T mapping_affine(const T& lhs, const T& rhs) {
	return {(rhs.b * lhs.b), (rhs.b * lhs.c + rhs.c)};
}
template<typename T> using affine_monotonic_queue = monotonic_queue<T, mapping_affine>;
