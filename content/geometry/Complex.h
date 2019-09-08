/**
 * Author: Chris
 * Date: 2019
 * License: CC0
 * Source:
 * Description: Exemple of geometry using complex numbers. Just to be used as reference. std::complex has issues with integral data types, be careful, you can't use polar or abs. 
 */

const double E = 1e-9;
typedef double T;
typedef complex<T> pt;
#define x real()
#define y imag()
// example of how to represent a line using complex numbers
struct line {
	pt p, v;
	line(pt a, pt b) {
		p = a;
		v = b - a;
	}
};

pt translate(pt v, pt p) {return p + v;}
//rotate point around origin by a
pt rotate(pt p, T a) { return p * polar(1.0, a); } 
//around pivot 
pt rotate(pt v, T a, pt pivot) { (a-pivot) * polar(1.0, a) + pivot; }
T dot(pt v, pt w) { return (conj(v)*w).x; }
T cross(pt v, pt w) { return (conj(v)*w).y; }
T cross(pt A, pt B, pt C) {
	return cross(B - A, C - A);
}
pt proj(pt a, pt v) {
	return v * dot(a, v) / dot(v, v);
}
 
pt closest(pt p, line l) {
	return l.p + proj(p - l.p, l.v);
}

double dist(pt p, line l) {
	return fabs(p - closest(p, l));
}

pt proj(pt p, line l) {
    return 
}

pt reflect(pt p, pt v, pt w) {
    pt z = p - v; pt q = w - v;
    return conj(z/q) * q + v;
}

pt intersection(line a, line b) { // undefined if parallel
    T d1 = cross(b.p - a.p, a.v - a.p);
    T d2 = cross(b.v - a.p, a.v - a.p);
    return (d1 * b.v - d2 * b.p)/(d1 - d2);
}

vector<pt> convex_hull(vector<pt> points) {
    if (points.size() <= 1) return points;
	sort(points.begin(), points.end(), [](pt a, pt b) { return real(a) == real(b) ? imag(a) < imag(b) : real(a) < real(b); });
	vector<pt> hull(points.size()+1);
	int s = 0, k = 0;
	for (int it = 2; it--; s = --k, reverse(points.begin(), points.end()))
	    for (pt p : points) {
	        while(k >= s+2 && cross(hull[k-2], hull[k-1], p) <= 0) k--;
	        hull[k++] = p;
	    }
	return {hull.begin(), hull.begin() + k - (k == 2 && hull[0] == hull[1])};
}


pt p{4, 3};
// get the absolute value and angle in [-pi, pi]
cout << abs(p) << ' ' << arg(p) << '\n'; // 5 - 0.643501

// make a point in polar form
cout << polar(2.0, -M_PI/2) << '\n'; // (1.41421, -1.41421)
pt v{1, 0};
cout << rotate(v, -M_PI/2) << '\n';
// Projection of v onto Riemann sphere and norm of p
cout << proj(v) << ' ' << norm(p) << '\n';
// Distance between p and v and the squared distance
cout << abs(v-p) << ' ' << norm(v-p) << '\n';
// Angle of elevation of line vp and its slope
cout << arg(p-v) * (180/M_PI) << ' ' << tan(arg(p-v)) << '\n';

// has trigonometric functions aswell (e.g. cos, sin, cosh, sinh, tan, tanh)
// and exp, pow, log

