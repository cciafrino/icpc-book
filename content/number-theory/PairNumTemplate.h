/**
 * Author: Chris
 * Description: Support pairs operations using modnum template. Pretty good for string hashing.
 * Source: https://codeforces.com/contest/1056/submission/46216123
 */
template <typename T, typename U> struct pairnum {
	T t;
	U u;
 
	pairnum() : t(0), u(0) {}
	pairnum(long long v) : t(v), u(v) {}
	pairnum(const T& t_, const U& u_) : t(t_), u(u_) {}
 
	friend std::ostream& operator << (std::ostream& out, const pairnum& n) { return out << '(' << n.t << ',' << ' ' << n.u << ')'; }
	friend std::istream& operator >> (std::istream& in, pairnum& n) { long long v; in >> v; n = pairnum(v); return in; }
 
	friend bool operator == (const pairnum& a, const pairnum& b) { return a.t == b.t && a.u == b.u; }
	friend bool operator != (const pairnum& a, const pairnum& b) { return a.t != b.t || a.u != b.u; }
 
	pairnum inv() const {
		return pairnum(t.inv(), u.inv());
	}
	pairnum neg() const {
		return pairnum(t.neg(), u.neg());
	}
	pairnum operator- () const {
		return pairnum(-t, -u);
	}
	pairnum operator+ () const {
		return pairnum(+t, +u);
	}
 
	pairnum& operator += (const pairnum& o) {
		t += o.t;
		u += o.u;
		return *this;
	}
	pairnum& operator -= (const pairnum& o) {
		t -= o.t;
		u -= o.u;
		return *this;
	}
	pairnum& operator *= (const pairnum& o) {
		t *= o.t;
		u *= o.u;
		return *this;
	}
	pairnum& operator /= (const pairnum& o) {
		t /= o.t;
		u /= o.u;
		return *this;
	}
 
	friend pairnum operator + (const pairnum& a, const pairnum& b) { return pairnum(a) += b; }
	friend pairnum operator - (const pairnum& a, const pairnum& b) { return pairnum(a) -= b; }
	friend pairnum operator * (const pairnum& a, const pairnum& b) { return pairnum(a) *= b; }
	friend pairnum operator / (const pairnum& a, const pairnum& b) { return pairnum(a) /= b; }
};
 
