/**
 * Author: Chris
 * Description: Number of permutations
 */
lint num_perm(int n, int r) {
    if (r < 0 || n < r) return 0;
    lint ret = 1;
    for (int i = n; i > n-r; --i) ret *= i;
    return ret;
}
