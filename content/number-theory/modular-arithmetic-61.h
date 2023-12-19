/**
 * Author: Chris
 * Date: 2021
 * License: CC0
 * Source: Yui Hosaka
 * Description: Operators for modular arithmetic mod (2^61-1). If you want to use
 * any other mod change operator *= (Use FastMod.h to reduce y).
 * Time:
 * Status: extensively used.
 */
#include"mod-inv.h"
template<int64_t M_ = (1ULL << 61)-1> struct modnum61 {
	using ll = int64_t; using ull = uint64_t; using T = ull;
	static constexpr T M = M_; T x; using num = modnum61;
	num& norm(T a){ x = a<M ? a : a-M; return *this; }
	constexpr modnum61(ll a = 0U) : x(T((a %= ll(M))<0 ? a+ll(M) : a)){}
	explicit operator int() const { return x; }
	num& operator+=(const num& a){ return norm(x+a.x); }
	num& operator-=(const num& a){ return norm(x-a.x+M); }
	num& operator*=(const num& a){
		const auto y = static_cast<__uint128_t>(x) * a.x;
		x = (y >> 61) + (y & M); return norm(x);
	}
	num& operator/=(const num& a){ return (*this *= a.inv());}
	num operator+(const num& a) const {return (num(*this) += a);}
	num operator-(const num& a) const {return (num(*this) -= a);}
	num operator*(const num& a) const {return (num(*this) *= a);}
	num operator/(const num& a) const {return (num(*this) /= a);}
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

