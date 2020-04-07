 
/**
 * Author: Chris
 * Description: Scanline (Merge all overalapping intervals into a single interval)
 * Usage: O(N)
 * Source: https://github.com/dragonslayerx 
 */
void scanline(vector<pair<int,int>> p, vector<pair<int,int>> &intervals) {
	int f = p[0].first, l = p[0].second;
	for (int i = 0; i < m; ++i) {
		if (p[i].first <= l) l = max(l, p[i].second);
		else {
			intervals.push_back({f, l});
			f = p[i].first, l = p[i].second;
		}
	}
	intervals.push_back({f, l});
}