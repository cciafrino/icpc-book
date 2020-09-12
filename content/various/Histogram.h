/**
 * Author: Chris
 * Date: 2020
 * License: CC0
 * Source: 
 * Time: 
 */
#include<RMQ.h>

template<typename T> struct MaxArea {
    rmq_t<T> rmq;
    MaxArea(const vector<T> &hist) : rmq(hist) {}
    T get_area(vector<T> &hist, int a, int b) { 
        assert(a <= b);
        if (a == b) return hist[a];
        int st = rmq.query(a, b).second;
        T res = (b - a + 1) * hist[st];
        T aux = get_area(hist, a, st-1);
        res = max(res, aux);
        aux = get_area(hist, st+1, b);
        res = max(res, aux);
        return res;
    }
};
