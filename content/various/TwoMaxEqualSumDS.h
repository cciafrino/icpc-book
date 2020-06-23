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
    int n = (int) v.size();
    int sum = accumulate(v.begin(), v.end(), 0);
    vector<int> dp(2*sum + 1, INT_MIN/2), newdp(2*sum + 1);
    int a, b, i; dp[sum] = 0;
    vector<vector<int>> rec(n, vector<int>(2*sum + 1));
    vector<int> s(n);   
    
    for(i=0; i<n; i++, swap(dp, newdp))
        for(int d = v[i] - sum; d <= sum - v[i]; d++){
            newdp[d + sum] = max({dp[d + sum], a = dp[d - v[i] + sum] + v[i], b = dp[d + v[i] + sum]});            
            auto &np = newdp[d + sum];
            rec[i][d + sum] = np == a ? 1 : np == b ? 2 : 0;
        }

    for(int j = i-1, bef=sum; j>=0 ; j--){
        s[j] = rec[j][bef];
        bef += s[j] ? s[j]==2 ? v[j] : -v[j] : 0;
    }
    return {dp[sum], s};
}

