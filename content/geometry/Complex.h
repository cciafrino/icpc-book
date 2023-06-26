/**
 * Author: Chris
 * Date: 2019
 * License: CC0
 * Source:
 * Description: Example of geometry using complex numbers. Just to be used as reference. std::complex has issues with integral data types, be careful, you can't use polar or abs. 
 */
const double E = 1e-9;
typedef double T;
using P = complex<T>;
#define x real()
#define y imag()
// example of how to represent a line using complex numbers
struct line {
	P p, v;
	line(P a, P b) {
		p = a;
		v = b - a;
	}
};
P dir(T angle) { return polar((T)1, angle); }
P unit(P p) { return p/abs(p); }
P translate(P v, P p) {return p + v;}
//rotate point around origin by a
P rotate(P p, T a) { return p * polar(1.0, a); } 
//around pivot 
P rotate(P v, T a, P pivot) { (a-pivot) * polar(1.0, a) + pivot; }
T dot(P v, P w) { return (conj(v)*w).x; }
T cross(P v, P w) { return (conj(v)*w).y; }
T cross(P A, P B, P C) { return cross(B - A, C - A); }
P proj(P a, P v) { return v * dot(a, v) / dot(v, v); }
P closest(P p, line l) { return l.p + proj(p - l.p, l.v); }
double dist(P p, line l) { return fabs(p - closest(p, l)); }
P reflect(P p, P v, P w) {
	P z = p - v; P q = w - v;
	return conj(z/q) * q + v;
}
P intersection(line a, line b) { // undefined if parallel
	T d1 = cross(b.p - a.p, a.v - a.p);
	T d2 = cross(b.v - a.p, a.v - a.p);
	return (d1 * b.v - d2 * b.p)/(d1 - d2);
}
vector<P> convex_hull(vector<P> points) {
	if (points.size() <= 1) return points;
	sort(points.begin(), points.end(), [](P a, P b) { 
		return real(a)==real(b) ? imag(a)<imag(b) : real(a)<real(b); });
	vector<P> hull(points.size()+1);
	int s = 0, k = 0;
	for (int it = 2; it--; s = --k, reverse(points.begin(), points.end()))
		for (P p : points) {
			while(k >= s+2 && cross(hull[k-2], hull[k-1], p) <= 0) k--;
			hull[k++] = p;
		}
	return {hull.begin(), hull.begin() + k - (k == 2 && hull[0] == hull[1])};
}
P p{4, 3};
// get the absolute value and angle in [-pi, pi]
cout << abs(p) << ' ' << arg(p) << '\n'; // 5 - 0.643501
										 // make a point in polar form
cout << polar(2.0, -M_PI/2) << '\n'; // (1.41421, -1.41421)
P v{1, 0};
cout << rotate(v, -M_PI/2) << '\n';
// Projection of v onto Riemann sphere and norm of p
cout << proj(v) << ' ' << norm(p) << '\n';
// Distance between p and v and the squared distance
cout << abs(v-p) << ' ' << norm(v-p) << '\n';
// Angle of elevation of line vp and its slope
cout << arg(p-v) * (180/M_PI) << ' ' << tan(arg(p-v)) << '\n';
// has trigonometric functions aswell (e.g. cos, sin, cosh, sinh, tan, tanh)
// and exp, pow, log

