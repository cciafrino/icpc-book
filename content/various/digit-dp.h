/**
 * Author: Felipe Chen
 * License: CC0
 * Source: 
 * Description: Compute how many # between 1 and N have K distinct digits in the base L without leading zeros;
 * Status: tested on https://atcoder.jp/contests/abc194/tasks/abc194_f
 * Usage: 
*  auto hex_to_dec = [&](char c) -> int { 
*	   return ('A' <= c && c <= 'F' ? (10 + c - 'A') : (c - '0')); 
*  };
*  digit_dp<modnum<int(1e9) + 7>, hex_to_dec>(N, K);
 * Time: O(NK)
 */
template<typename T, class F> T digit_dp(string& S, int K, F& L) {
	const int base = 16;
	const int len = int(S.size());

	vector<bool> w(base);
	vector<vector<T>> dp(len + 1, vector<T>(base + 2));
	
	int cnt = 0;
	for (int d = 0; d < len; ++d) {
		for (int x = 0; x <= base; ++x) {
			dp[d + 1][x] += dp[d][x] * x;
			dp[d + 1][x + 1] += dp[d][x] * (base - x);
		}
		if (d) dp[d + 1][1] += (base - 1);
		for (int x = 0; x < L(S[d]); ++x) {
			if (d == 0 && x == 0) continue;
			if (w[x]) dp[d + 1][cnt] += 1;
			else dp[d + 1][cnt + 1] += 1;
		}
		if (w[L(S[d])] == false) {
			w[L(S[d])] = true;
			cnt++;
		}
	}
	dp[len][cnt] += 1;
	return dp[len][K];
}
