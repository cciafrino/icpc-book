/**
 * Author: Chris
 * Date: 2024
 * License: 
 * Source: 
 * Description:  implementation of the root of unity using complex numbers.
 */
template <typename dbl> struct cplx { ///start-hash
	dbl x, y; using P = cplx;
	cplx(dbl x_ = 0, dbl y_ = 0) : x(x_), y(y_) { }
	friend P operator+(P a, P b) { return P(a.x+b.x, a.y+b.y); }
	friend P operator-(P a, P b) { return P(a.x-b.x, a.y-b.y); }
	friend P operator*(P a, P b) { return P(a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x); }
	friend P conj(P a) { return P(a.x, -a.y); }
	friend P inv(P a) { dbl n = (a.x*a.x+a.y*a.y); return P(a.x/n,-a.y/n); }
};
template <typename T> struct root_of_unity {};
template <typename dbl> struct root_of_unity<cplx<dbl>> {
	static cplx<dbl> f(int k) {
		static const dbl PI = acos(-1); dbl a = 2*PI/k;
		return cplx<dbl>(cos(a),sin(a));
	}
}; ///end-hash