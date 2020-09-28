/**
 * Author: Chris
 * Date: 2020
 * License: CC0
 * Source: kactl
 * Description: Answer interval or tree path queries by finding an approximate TSP through the queries,
 * and moving from one query to the next by adding/removing points at the ends. Mo's algorithm example problem: Count how many elements appear at least two times in given range $[l, r]$.
 * For path queries on trees, flatten the tree by DFSing and pushing even-depth nodes at entry and odd-depth nodes at exit.
 * Time: O(N \sqrt Q)
 * Status: Tested on SPOJ DQUERY and kattis farmingmars
 */
template<typename T>
vector<T> mo(vector<array<int,2>>& Q, vector<int>& A) {
	const int sqn = 370; // ~ N/sqrt(Q)
	vector<int> s(int(Q.size()));
	iota(s.begin(), s.end(), 0);
#define K(x) make_pair(x[0]/sqn, x[1] ^ -(x[0]/sqn & 1))
	sort(s.begin(), s.end(), [&](int x, int y) { return K(Q[x]) < K(Q[y]); });
	const int ma = 100100; // max value in freq table
	vector<T> result(int(Q.size()));
	vector<int> freq(ma+1);
	int L = 0, R = 0;
	T cur = 0;
	for (auto& qi : s) {
		auto q = Q[qi];
		auto add = [&](int i) { // add
			++freq[A[i]];
			if (freq[A[i]] == 2) cur += 2;
			else if (freq[A[i]] > 2) ++cur;
		};
		auto del = [&](int i) { // remove
			--freq[A[i]];
			if (freq[A[i]] == 1) cur -= 2;
			else if (freq[A[i]] > 1) --cur;
		};
		while(R < q[1]) add(++R);
		while(L > q[0]) add(--L);
		while(R > q[1]) del(R--);
		while(L < q[0]) del(L++);
		result[qi] = cur; 
	}
	return result;
}
