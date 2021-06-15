/**
 * Author: Simon Lindholm
 * Date: 2018-07-06
 * License: CC0
 * Source: http://antoinecomeau.blogspot.com/2014/07/mapping-between-permutations-and.html
 * Description: Permutation -> integer conversion. (Not order preserving.)
 * Time: O(n)
 */
int permToInt(vector<int>& v) {
	int use = 0, i = 0, r = 0;
	for (auto &x : v) r=r * ++i + __builtin_popcount(use & -(1 << x)),
		use |= 1 << x;                // (note: minus, not ~!)
	return r;
}
