/**
 * Author: Neal Wu
 * Description: Radix Sort Algorithm. 
 * Time: $O(NK)$ where $K$ is the number of bits in the largest element of the array to be sorted. 
 * Source: https://erik.gorset.no/2011/04/radix-sort-is-faster-than-quicksort.html
 */
struct identity {
	template<typename T>
		T operator()(const T &x) const {
			return x;
		}
};
template<typename T, typename T_extract_key = identity>
void radix_sort(vector<T> &data, int bits_per_pass = 10, const T_extract_key &extract_key = identity()) {
	if (data.size() < 256) {
		sort(data.begin(), data.end(), [&](const T &a, const T &b) {
			return extract_key(a) < extract_key(b);
		});
		return;
	}
	using T_key = decltype(extract_key(data.front()));
	T_key minimum = numeric_limits<T_key>::max();
	for (T &x : data) minimum = min(minimum, extract_key(x));
	int max_bits = 0;
	for (T &x : data) {
		T_key key = extract_key(x);
		max_bits = max(max_bits, key == minimum ? 0 : 64 - __builtin_clzll(key - minimum));
	}
	int passes = max((max_bits + bits_per_pass / 2) / bits_per_pass, 1);
	if (32 - __builtin_clz(data.size()) <= 1.5 * passes) {
		sort(data.begin(), data.end(), [&](const T &a, const T &b) {
			return extract_key(a) < extract_key(b);
		});
		return;
	} 
	vector<T> buffer(data.size());
	vector<int> counts;
	int bits_so_far = 0;
	for (int p = 0; p < passes; p++) {
		int bits = (max_bits + p) / passes;
		counts.assign(1 << bits, 0);
		for (T &x : data) {
			T_key key = extract_key(x) - minimum;
			counts[(key >> bits_so_far) & ((1 << bits) - 1)]++;
		}
		int count_sum = 0;
		for (int &count : counts) {
			int current = count;
			count = count_sum;
			count_sum += current;
		}
		for (T &x : data) {
			T_key key = extract_key(x) - minimum;
			int key_section = (key >> bits_so_far) & ((1 << bits) - 1);
			buffer[counts[key_section]++] = x;
		}
		swap(data, buffer);
		bits_so_far += bits;
	}
}
