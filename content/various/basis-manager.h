/**
 * Author: Neal Wu
 * Source: https://math.stackexchange.com/questions/48682/maximization-with-xor-operator
 * Description: A list of basis values sorted in decreasing order, where each value has a unique highest bit.
 * Status: tested on kattis
 */
const int BITS = 60;

template<typename T> struct xor_basis {
	int N = 0;
	array<T, BITS> basis;

	T min_value(T start) const {
		if (N == BITS) return 0;
		for (int i = 0; i < N; ++i)
			start = min(start, start ^ basis[i]);
		return start;
	}
	T max_value(T start = 0) const {
		if (N == BITS) return ((T) 1 << BITS) - 1;
		for (int i = 0; i < N; ++i)
			start = max(start, start ^ basis[i]);
		return start;
	}
	bool add(T x) {
		x = min_value(x);
		if (x == 0) return false;
		basis[N++] = x;
		// Insertion sort.
		for (int k = N - 1; k > 0 && basis[k] > basis[k - 1]; k--)
			swap(basis[k], basis[k - 1]);
		return true;
	}
	void merge(const xor_basis<T>& other) {
		for (int i = 0; i < other.n && N < BITS; i++)
			add(other.basis[i]);
	}
	void merge(const xor_basis<T>& a, const xor_basis<T>& b) {
		if (a.N > b.N) {
			*this = a;
			merge(b);
		} else {
			*this = b;
			merge(a);
		}
	}
};
