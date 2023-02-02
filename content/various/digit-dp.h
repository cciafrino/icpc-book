/**
 * Author: Felipe Chen
 * License: CC0
 * Source: 
 * Description: Compute how many \# between 1 and $N$ have $K$ distinct digits in the base $L$ without leading zeros;
 * Status: tested on https://atcoder.jp/contests/abc194/tasks/abc194_f
 * Usage: 
*  auto hex_to_dec = [\&](char c) -> int { 
*	   return ('A' <= c \&\& c <= 'F' ? (10 + c - 'A') : (c - '0')); 
*  };
*  digit_dp<modnum<int(1e9) + 7>, hex_to_dec>(N, K);
 * Time: O(NK)
 */
template<typename T, class F> T digit_dp(const string& S, int K, F& L) {
    const int base = 16;
    const int len = int(S.size());

    vector<bool> w(base);
    vector<vector<T>> dp(len + 1, vector<T>(base + 2));

    int cnt = 0;
    for (int d = 0; d < len; ++d) {
        // adding new digit to numbers wiht prefix < s
        for (int x = 0; x <= base; ++x) {
            dp[d + 1][x] += dp[d][x] * x;
            dp[d + 1][x + 1] += dp[d][x] * (base - x);
        }
        // adding strings whith prefix only 0's and last digit != 0
        if (d) dp[d + 1][1] += (base - 1);
        // adding prefix equal to s and last digit < s, first digit cannot be 0
        for (int x = 0; x < L(S[d]); ++x) {
            if (d == 0 && x == 0) continue;
            if (w[x]) dp[d + 1][cnt] += 1;
            else dp[d + 1][cnt + 1] += 1;
        }
        // marking if the last digit appears in the prefix of s
        if (w[L(S[d])] == false) {
            w[L(S[d])] = true;
            cnt++;
        }
    }
    // adding string k
    dp[len][cnt] += 1;
    return dp[len][K];
}
