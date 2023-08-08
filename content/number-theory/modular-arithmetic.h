/**
 * Author: Chris
 * Date: 2021
 * License: CC0
 * Source: Yui Hosaka
 * Description: Operators for modular arithmetic. 
 * Time:
 * Status: extensively used.
 */
#include"mod-inv.h"
template<unsigned M_> struct modnum {
	static constexpr unsigned M = M_;
	using ll = int64_t; using ull = uint64_t; unsigned x;
	modnum& norm(unsigned a) { x = a < M ? a : a - M; return *this; }
	constexpr modnum(ll a = 0U) : x(unsigned((a %= ll(M)) < 0 ? a + ll(M) : a)) {}
	explicit operator int() const { return x; }
	modnum& operator+=(const modnum& a) { return norm(x + a.x); }
	modnum& operator-=(const modnum& a) { return norm(x - a.x + M); }
	modnum& operator*=(const modnum& a) { x = unsigned(ull(x) * a.x % M); return *this; }
	modnum& operator/=(const modnum& a) { return (*this *= a.inv()); }
	modnum operator+(const modnum& a) const { return (modnum(*this) += a); }
	modnum operator-(const modnum& a) const { return (modnum(*this) -= a); }
	modnum operator*(const modnum& a) const { return (modnum(*this) *= a); }
	modnum operator/(const modnum& a) const { return (modnum(*this) /= a); }
	template<typename T> friend modnum operator+(T a, const modnum& b) { return (modnum(a) += b); }
	template<typename T> friend modnum operator-(T a, const modnum& b) { return (modnum(a) -= b); }
	template<typename T> friend modnum operator*(T a, const modnum& b) { return (modnum(a) *= b); }
	template<typename T> friend modnum operator/(T a, const modnum& b) { return (modnum(a) /= b); }
	modnum operator+() const { return *this; }
	modnum operator-() const { return modnum() - *this; }
	modnum pow(ll e) const {
		if (e < 0) return inv().pow(-e);
		modnum b = x, xe = 1U;
		for (; e; e >>= 1) { if (e & 1) xe *= b; b *= b; }
		return xe;
	}
	modnum inv() const { return minv(x, M); }
	friend modnum inv(const modnum& a) { return a.inv(); }
	explicit operator bool() const { return x; }
	friend bool operator==(const modnum& a, const modnum& b) { return a.x == b.x; }
	friend bool operator!=(const modnum& a, const modnum& b) { return a.x != b.x; }
	friend ostream &operator<<(ostream& os, const modnum& a) { return os << a.x; }
	friend istream &operator>>(istream& in, modnum& n) { ll v_; in >> v_; n = modnum(v_); return in; }
};
