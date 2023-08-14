/**
 * Author: Chris
 * Description: failure[x] computes the length of the longest prefix of s that ends at x, other than s[0...x] itself (abacaba -> -1,0,0,1,0,1,2,3).
 * Can be used to find all occurrences of a pattern in a text.
 * Time: O(n)
 */
vector<int> prefix_function(const string& S) {
	vector<int> fail = {-1}; fail.reserve(S.size());
	for (int i = 0; i < int(S.size()); ++i) {
		int j = fail.back();
		while (j != -1 && S[i] != S[j]) j = fail[j];
		fail.push_back(j+1);
	}
	return fail;
}
