/**
 * Author: Chris
 * Description: Operators for modular arithmetic. You need to set 
 * {\tt mod} to some number first and then you can use the structure.
 */
 
template <int MOD_>  struct modnum {
private:
	using lint = long long;
	lint v;
	static int modinv(int a, int m) {
		a %= m;
		assert(a);
		return a == 1 ? 1 : int(m - lint(modinv(m, a)) * lint(m) / a);
	}
public:
	static constexpr int MOD = MOD_;
	modnum() : v(0) {}
	modnum(lint v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
	explicit operator int() const { return v; }
	friend std::ostream &operator<<(std::ostream& out, const modnum& n) { return out << int(n); }
	friend std::istream &operator>>(std::istream& in, modnum& n) { lint v_; in >> v_; n = modnum(v_); return in; }
	friend bool operator==(const modnum& a, const modnum& b) { return a.v == b.v; }
	friend bool operator!=(const modnum& a, const modnum& b) { return a.v != b.v; }
	modnum inv() const {
		modnum res;
		res.v = modinv(v, MOD);
		return res;
	}
	modnum neg() const {
		modnum res;
		res.v = v ? MOD-v : 0;
		return res;
	}
	modnum operator-() const { return neg(); }
	modnum operator+() const { return modnum(*this); }
	modnum& operator+=(const modnum& o) {
		v += o.v;
		if (v >= MOD) v -= MOD;
		return *this;
	}
	modnum& operator-=(const modnum& o) {
		v -= o.v;
		if (v < 0) v += MOD;
		return *this;
	}
	modnum& operator*=(const modnum& o) {
		v = int(lint(v) * lint(o.v) % MOD);
		return *this;
	}
	modnum& operator/=(const modnum& o) { return *this *= o.inv(); }
	friend modnum operator+(const modnum& a, const modnum& b) { return modnum(a) += b; }
	friend modnum operator-(const modnum& a, const modnum& b) { return modnum(a) -= b; }
	friend modnum operator*(const modnum& a, const modnum& b) { return modnum(a) *= b; }
	friend modnum operator/(const modnum& a, const modnum& b) { return modnum(a) /= b; }
};
 
template <typename T> T pow(T a, lint b) {
	assert(b >= 0);
	T r = 1; while (b) { if (b & 1) r *= a; b >>= 1; a *= a; } return r;
}

using num = modnum<int(1e9)+7>;

 
