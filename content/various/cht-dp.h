/**
 * Author: Arthur Pratti Dadalto
 * License: CC0
 * Source: Codeforces
 * Description: Transforms dp of the form (or similar) $dp[i] = min_{j < i}(dp[j] + b[j] * a[i]$).
		Time goes from $O(n^2)$ to $O(n \log n)$, if using online line container, or $O(n)$ if
		lines are inserted in order of slope and queried in order of $x$.
		To apply try to find a way to write the factor inside minimization as a linear function
		of a value related to i. Everything else related to j will become constant.
 * Status: tested on https://codeforces.com/contest/319/problem/C
 */
