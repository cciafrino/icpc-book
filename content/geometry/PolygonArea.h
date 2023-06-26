/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: tinyKACTL
 * Description: Returns the area of a polygon.
 *  Clockwise enumeration gives negative area. Watch out for overflow if using int as T!
 * Status: Tested with unitTest, Kattis problems polygonarea and wrapping and UVa Online Judge Problem: 109 - SCUD Busters
 */
#include "Point.h"
template<class T>
T polygonArea(vector<Point<T>> &v) {
	T a = v.back().cross(v[0]);
	for(int i = 0; i < v.size()-1; ++i) 
		a += v[i].cross(v[i+1]);
	return abs(a)/2.0;
}

Point<T> polygonCentroid(vector<Point<T>> &v) { // not tested
	Point<T> cent(0,0); T area = 0;
	for(int i = 0; i < v.size(); ++i) {
		int j = (i+1) % (v.size()); T a = cross(v[i], v[j]);
		cent += a * (v[i] + v[j]);
		area += a;
	}
	return cent/area/(T)3;
}
