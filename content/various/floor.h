/**
 * Author: Chris
 * License: 
 * Description: 
 * Status: slightly tested
 * Time: 
 */
template<typename T> T mfloor(T a, T b) {
    return a / b - (((a ^ b) < 0 && a % b != 0) ? 1 : 0);
}

template<typename T> T mceil(T a, T b) {
    return a / b + (((a ^ b) > 0 && a % b != 0) ? 1 : 0);
}
