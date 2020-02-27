/**
 * Author: Chris
 * License: 
 * Description:
 * Status:
 * Time: 
 */
 
unordered_map<int, int> dp;
lint fib(int n) {
    if (n < 2) return 1;
    if (dp.find(n) != dp.end()) return dp[n];
    return dp[n] = (fib((n+1)/2) * fib(n/2) + fib((n-1)/2) * fib((n-2)/2));
}
