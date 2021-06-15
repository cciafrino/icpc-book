/**
 * Author: ?
 * Source: Macacario 
 * Description: Check if an array of degrees can represent a graph
 * Time: if sorted $O(n)$, otherwise $O(nlog(n))$
 */

bool EG(vector<int> deg) {
    sort(deg.begin(), deg.end(), greater<int>());
    vector<long long> dp(deg.size());
    int n = deg.size(), p = n-1;
    for(int i = 0; i < n; i++)
        dp[i] = deg[i] + (i > 0 ? dp[i-1] : 0);
    for(int k = 1; k <= n; k++) {
        while(p >= 0 && deg[p] < k) p--;
        long long sum;
        if (p >= k-1) sum = (p-k+1)*1ll*k + dp[n-1] - dp[p];
        else sum = dp[n-1] - dp[k-1];
        if (dp[k-1] > k*(k-1LL) + sum) return 0;
    }
    return dp[n-1] % 2 == 0;
}