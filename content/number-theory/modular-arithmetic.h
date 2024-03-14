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
	static constexpr unsigned M = M_; using num = modnum;
	using ll = int64_t; using ull = uint64_t; unsigned x;
	num& norm(unsigned a){x = a<M ? a : a-M;return *this;}
	constexpr modnum(ll a = 0U) { norm(unsigned(a % M + M)); }
	explicit operator int() const { return x; }
	num& operator+=(const num& a){ return norm(x+a.x); }
	num& operator-=(const num& a){ return norm(x-a.x+M); }
	num& operator*=(const num& a){ return norm(unsigned(ull(x)*a.x % M)); }
	num& operator/=(const num& a){ return (*this *= a.inv());}
	template<typename T> friend num operator+(T a, const num& b){ return (num(a) += b); }
	template<typename T> friend num operator-(T a, const num& b){ return (num(a) -= b); }
	template<typename T> friend num operator*(T a, const num& b){ return (num(a) *= b); }
	template<typename T> friend num operator/(T a, const num& b){ return (num(a) /= b); }
	num operator+() const { return *this; }
	num operator-() const { return num() - *this; }
	num pow(ll e) const {
		if (e < 0) { return inv().pow(-e); } num b = x, xe = 1U;
		for (; e; e >>= 1) { if (e & 1) xe *= b; b *= b; }
		return xe;
	}
	num inv() const { return minv(x, M); }
	friend num inv(const num& a) { return a.inv(); }
	explicit operator bool() const { return x; }
	friend bool operator==(const num& a, const num& b){return a.x == b.x;}
	friend bool operator!=(const num& a, const num& b){return a.x != b.x;}
};