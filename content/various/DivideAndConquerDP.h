/**
 * Author: Arthur Pratti Dadalto
 * License: CC0
 * Source: Codeforces
 * Description: Optimizes dp of the form (or similar) $dyn[i][j] = min_{k < i}(dyn[k][j-1] + f(k + 1, i))$.
		The classical case is a partitioning $dp$, where k determines the break point for the next partition.
		In this case, $i$ is the number of elements to partition and $j$ is the number of partitions allowed.
		
		Let $opt[i][j]$ be the values of $k$ which minimize the function. (in case of tie, choose the smallest)
		To apply this optimization, you need $opt[i][j] \leq opt[i+1][j]$.
		That means the when you add an extra element $(i + 1)$, your partitioning choice will not be to include more elements
		than before (e.g. will no go from choosing $[k, i]$ to $[k-1, i+1]$).
		This is usually intuitive by the problem details.
		
		.
		To apply try to write the dp in the format above and verify if the property holds.
 * Status: tested on http://codeforces.com/contest/321/problem/E
 * Time: Time goes from $O(n^2m)$ to $O(nm \log(n))$
 */
const int INF = 1<<31;
int n, m;
template<typename MAXN, typename MAXM>
struct dp_task {
    array<array<int, MAXN>, MAXN> u;
    array<array<int, MAXN>, MAXM> dyn;
    inline f(int i, int j) {
        return (u[j][j] - u[j][i-1] - u[i-1][j] + u[i-1][i-1]) / 2;
    }
    // This is responsible for computing tab[l...r][j], knowing that opt[l...r][j] is in range [low_opt...high_opt]
    void solve(int j, int l, int r, int low_opt, int high_opt) {
        int mid = (l + r) / 2, opt = -1;
        dyn[mid][j] = INF;
        for (int k = low_opt; k <= high_opt && k < mid; ++k) 
            if (dyn[k][j-1] + f(k + 1, mid) < dyn[mid][j]) {
                dyn[mid][j] = dyn[k][j-1] + f(k + 1, mid);
                opt = k;
            }
	    // New bounds on opt for other pending computation.
	    if (l <= mid - 1)
		    solve(j, l, mid - 1, low_opt, opt);
	    if (mid + 1 <= r)
		    solve(j, mid + 1, r, opt, high_opt);
    }
};

int main() {
    dp_task<4123, 812> DP;
    cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) 
            cin >> DP.u[i][j];
		
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			DP.u[i][j] += DP.u[i - 1][j] + DP.u[i][j - 1] - DP.u[i - 1][j - 1];

	for (int i = 1; i <= n; i++)
		DP.dyn[i][0] = INF;

	// Original dp
	// for (int i = 1; i <= n; i++)
	// 	for (int j = 1; j <= m; j++) {
	// 		dyn[i][j] = INF;
	// 		for (int k = 0; k < i; k++)
	// 			dyn[i][j] = min(dyn[i][j], dyn[k][j-1] + f(k + 1,i);
	// 	}

	for (int j = 1; j <= m; j++)
		DP.solve(j, 1, n, 0, n - 1);

	cout << DP.dyn[n][m] << endl;
}

