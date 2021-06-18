/**
 * Author: 
 * Date: 
 * License: 
 * Source: https://github.com/victorsenam/caderno/blob/master/code/zeta.cpp
 * Description: 
 * Usage: To calculate c[i] = sum (a[j] * b[k]) st j | k == i
 * Use c = itf(tf(a) * tf(b)), where * is element by element multiplication
 * Common transformations and inverses:
 * OR  - (a, b) => (a, a + b)     | (a, b) => (a, b - a)
 * AND - (a, b) => (a + b, b)     | (a, b) => (a - b, b)
 * XOR - (a, b) => (a + b, a - b) | (a, b) => ((a + b) / 2, (a - b) / 2)
 *
 * Time: O(N \log N) 
 * Status: not tested
 */

// Transform a inplace (OR), initially l = 0, r = 2^n - 1
void tf(vector<lint> &a, int l, int r) {
    if (l == r) return;
    int m = (l + r)/2;
    tf(a, l, m); tf(a, m+1, r);
    for (int i = l; i <= m; ++i)
        a[m + (i - l) + 1] += a[i];
}

// Inverse transforms a inplace (OR), initially l = 0, r = 2^n - 1
void inverse_tf(vector<lint> &a, int l, int r) {
    if (l == r) return;
    int m = (l + r)/2;
    for (int i = l; i <= m; ++i)
        a[m + (i - l) + 1] -= a[i];   
    inverse_tf(a, l, m); inverse_tf(a, m+1, r);
}
