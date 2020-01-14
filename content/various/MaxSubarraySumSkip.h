/**
 * Author: Chris
 * Source: 
 * Description: Computes the subarray with the maximum sum, removing at most one element from the array.
 * Time: $O(N)$
 * 
 */
const int MAXN = 100, MAXM = 100;
array<int, MAXN> A, fw, bw;
int solve(int N) {
    T curMax = fw[0] = A[0], maxSum = A[0];
    for (int i = 1; i < N; i++) { fw[i] = curMax = max(A[i], curMax + A[i]); maxSum = max(maxSum, curMax); }
    curMax = maxSum = bw[N - 1] = A[N - 1];
    for (int i = N - 2; i >= 0; i--) { bw[i] = curMax = max(A[i], curMax + A[i]); maxSum = max(maxSum, curMax); }
    for (int i = 1; i < N - 1; i++) maxSum = max(maxSum, fw[i - 1] + bw[i + 1]);
    return maxSum;
}
