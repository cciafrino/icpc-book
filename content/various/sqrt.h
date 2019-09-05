/**
 * Author: Chris
 * Description: 
 */

int64_t isqrt(int64_t n) {
    int64_t left = 0;
    int64_t right = 10000000;
    while (right - left > 1) {
        int64_t middle = (left + right) / 2;
        if (middle * middle <= n) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return left;
}
