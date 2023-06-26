/**
 * Author: Rodrigo Zhou
 * Description: 
 * Time: $O(N\log(N))$
 */

vector<int> merge(vector<int> &values, int l, int r) {
	static vector<int> result(values.size());
	int i = l, j = l + (r - l)/2;
	int mid = j, k = i, inversions = 0;
	while (i < mid && j < r) {
		if (values[i] < values[j]) result[k++] = values[i++];
		else {
			result[k++] = values[j++];
			inversions += (mid - i);
		}
	}
	while (i < mid) result[k++] = values[i++];
	while (j < r) result[k++] = values[j++];
	for (k = l; k < r; ++k) values[k] = result[k];
	return result;
}

vector<int> msort(vector<int> &values, int l, int r) {
	if (r - l > 1) {
		int mid = l + (r - l)/2;
		msort(values, l, mid); msort(values, mid, r);
		return merge(values, l, r);
	}
	return {};
}
