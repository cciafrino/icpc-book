/**
 * Author: LeticiaFCS
 * License: CC0
 * Description: Two maximum equal sum disjoint subsets,
 * s[i] = 0 if v[i] wasn't selected, s[i] = 1 if v[i] is
 * in the first subset and s[i] = 2 if v[i] is in the
 * second subset
 * Status: tested on URI1700 and leetcode Tallest Billboard
 * Time: $O(n * max sum)$
 */

pair<int, vector<int>> twoMaxEqualSumDS(vector<int> &v){
    int i, n = (int) v.size();
    int sum = accumulate(v.begin(), v.end(), 0);
    vector<int> dp(2*sum + 1, INT_MIN/2), newdp(2*sum + 1);
    dp[sum] = 0;
    vector<vector<int>> rec(n, vector<int>(2*sum + 1));
    vector<int> s(n);   
    
    for(i=0; i<n; i++, swap(dp, newdp))
        for(int a, b, d = v[i]; d <= 2*sum - v[i]; d++){
            newdp[d] = max({dp[d], a = dp[d - v[i]] + v[i], b = dp[d + v[i]]});
            rec[i][d] = newdp[d] == a ? 1 : newdp[d] == b ? 2 : 0;
        }

    for(int j = i-1, d=sum; j>=0 ; j--)
        d += (s[j] = rec[j][d]) ? s[j] == 2 ? v[j] : -v[j] : 0;
    
    return {dp[sum], s};
}

