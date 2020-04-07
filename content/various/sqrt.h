/**
 * Author: Chris
 * Description: 
 */

template<typename T> T isqrt(T n) {
    T left = 0, right = 10000000;
    while (right - left > 1) {
        T mid = (left + right)/2;
        if (mid * mid <= n) left = mid;
        else right = mid;
    }
    return left;
}
