/**
 * Author: BenQ (adapted by LeticiaFCS)
 * Date: 
 * License: 
 * Source: 
 * Description: Template that helps deal with frtions.
 */
template<typename num> struct fraction_t {
	num p, q; using fr = fraction_t;
	fraction_t() : p(0), q(1) { }
	fraction_t(num _n, num _d = 1): p(_n), q(_d){
		num g = gcd(p, q); p /= g, q /= g;
		if (q < 0) p *= -1, q *= -1; assert(q != 0);
	}
	friend bool operator<(const fr& l, const fr& r){
		return l.p*r.q < r.p*l.q;}
	friend bool operator==(const fr& l, const fr& r){return l.p == r.p && l.q == r.q;}
	friend bool operator!=(const fr& l, const fr& r){return !(l == r);}
	friend fr operator+(const fr& l, const fr& r){
		num g = gcd(l.q, r.q);
		return fr(r.q / g * l.p + l.q / g * r.p, l.q / g * r.q);
	}
	friend fr operator-(const fr& l, const fr& r) {
		num g = gcd(l.q, r.q);
		return fr( r.q / g * l.p - l.q / g * r.p, l.q / g * r.q);
	}
	friend fr operator*(const fr& l, const fr& r){
		return fr(l.p*r.p, l.q*r.q);}
	friend fr operator/(const fr& l, const fr& r){
		return l*fr(r.q,r.p);}
	friend fr& operator+=(fr& l, const fr& r){return l=l+r;}
	friend fr& operator-=(fr& l, const fr& r){return l=l-r;}
	template<class T> friend fr& operator*=(fr& l, const T& r){return l=l*r;}
	template<class T> friend fr& operator/=(fr& l, const T& r){return l=l/r;}
};
