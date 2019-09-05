/**
 * Author: Chris
 * Description:
 */
c[0][0] = 1;
for (int i = 0; i < n; ++i) {
    c[i][0] = 1;
    for (int j = 1; j <= i; ++j)
        c[i][j] = c[i-1][j-1] + c[i-1][j];
}
