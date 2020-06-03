/**
 * Author: Chris
 * Description: Count the number of inversions to make an array sorted. Merge sort has another approach.
 * Time: $O(nlog(n))$
 */
#include<FenwickTree.h>

FT<lint> bit(n);    
lint inv = 0;
for (int i = n-1; i >= 0; --i) {
    inv += bit.query(values[i]); // careful with the interval 
    bit.update(values[i], 1);    // [0, x) or [0, x] ?
}

// using D&C,the constant is quite high but still nlogn
lint msort(vector<int> &values, int left, int right) {
	if ((right - left) <= 1) return 0;
	int mid = left + (right - left)/2;
	lint result = msort(values, left, mid) + msort(values, mid, right);
	auto cmp = [](int i, int j) { return i > j; };
	sort(values.begin() + left, values.begin() + mid, cmp);
	sort(values.begin() + mid, values.begin() + right, cmp);
	int pos = left;
	for (int i = mid; i < right; ++i) {
		while (pos != mid && values[pos] > values[i]) ++pos;
		result += (pos - left);
	}
	return result;
}
