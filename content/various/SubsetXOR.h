/**
 * Author: Chris
 * Source: https://math.stackexchange.com/questions/48682/maximization-with-xor-operator
 * Description: Given an array compute the maximum/minimum subset xor.
 * Status: tested on kattis
 */

template<typename T> struct XorGauss {
    int n; vector<T> a;
    XorGauss(int bits) : n(bits), a(bits) {}
    T reduce(T x) {
        for(int i = n-1; i >= 0; i--) 
            x = max(x, x ^ a[i]);
        return x;
    }
    T augment(T x) { return ~reduce(~x); }
    bool add(T x) {
        for(int i = n-1; i >= 0; i--) {
            if (!(x & (1ll << i))) continue;
            if (a[i]) x ^= a[i];
            else {
                a[i] = x;
                return true;
            }
        }
        return false;
    }
};