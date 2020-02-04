/**
 * Author: Simon Lindholm and Arthur Pratti Dadalto
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: When doing DP on intervals: $a[i][j] = \min_{i < k < j}(a[i][k] + a[k][j]) + f(i, j)$, where the (minimal) optimal $k$ increases with both $i$ and $j$,
 *  one can solve intervals in increasing order of length, and search $k = p[i][j]$ for $a[i][j]$ only between $p[i][j-1]$ and $p[i+1][j]$.
 *  This is known as Knuth DP. Sufficient criteria for this are if $f(b,c) \le f(a,d)$ and $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$ for all $a \le b \le c \le d$.
 *  Generally, Optimizes dp of the form (or similar) $dp[i][j] = min_{i <= k <= j}(dp[i][k-1] + dp[k+1][j] + f(i, j))$.
 *  The classical case is building a optimal binary tree, where k determines the root.
 *  Let $opt[i][j]$ be the value of $k$ which minimizes the function. (in case of tie, choose the smallest)
 *  To apply this optimization, you need $opt[i][j - 1] \leq opt[i][j] \leq opt[i+1][j]$.
 *  That means the when you remove an element form the left $(i + 1)$, you won't choose a breaking point more to the left than before.
 *  Also, when you remove an element from the right $(j - 1)$, you won't choose a breking point more to the right than before.
 *  This is usually intuitive by the problem details.
 *  To apply try to write the dp in the format above and verify if the property holds.
 *  Be careful with edge cases for $opt$.
 *  Consider also: LineContainer (ch. Data structures), monotone queues, ternary search.
 * Status: tested on https://www.spoj.com/problems/BRKSTRNG/
 * Time: from $O(N^3)$ to $O(N^2)$
 */
 
array<array<lint, 1123>, 1123> dp;
array<array<int, 1123>, 1123> opt;
array<int, 1123> b;
int l, n;

inline f(int i, int j) {
    return b[j+1] - b[i-1];
}

int main() {
    while(cin >> l >> n) {
        for (int i = 1; i <= n; ++i) cin >> b[i];
        b[0] = 0;
        b[n + 1] = l;
        for (int i = 1; i <= n+1; ++i) {
            dp[i][i - 1] = 0 
            opt[i][i - 1] = i;    
        }
        for (int i = n; i > 0; --i) 
            for (int j = i; j <= n; ++j) {
                dp[i][j] = LLONG_MAX; // INF
                for (int k = max(i, opt[i][j - 1]); k <= j && k <= opt[i + 1][j]; ++k)
                    if (dp[i][k - 1] + dp[k + 1][j] + f(i, j) < dp[i][j]) {
                        dp[i][j] = dp[i][k - 1] + dp[k + 1][j] + f(i, j);
                        opt[i][j] = k;
                    }
            }
        cout << dp[1][n] << '\n';
    }
}
