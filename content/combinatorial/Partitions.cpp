/**
 * Author: Snapdragon
 * Date: 2019
 * License: CC0
 * Description: Fills array with partition function p(n) for 0 <= i <= n
 */

array<int, 122> part; // 121 is max partition that will fit into int
void partition(int n) {
    part[0] = 1;
    for (int i = 1; i <= n; ++i) {
        part[i] = 0;
        for (int k = 1, x; k <= i; ++k) {
            x = i - k * (3*k-1)/2;
            if (x < 0) break;
            if (k&1) part[i] += part[x];
            else part[i] -= part[x];
            x = i - k * (3*k+1)/2;
            if (x < 0) break;
            if (k&1) part[i] += part[x];
            else part[i] -= part[x];
        }
    }
}
