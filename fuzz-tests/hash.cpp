#include<bits/stdc++.h>
using namespace std;

using lint = long long;

template <int MOD_> struct modnum {
	static constexpr int MOD = MOD_;
	static_assert(MOD_ > 0, "MOD must be positive");
private:
	using ll = long long;
 
	ll v;
 
	static int minv(int a, int m) {
		a %= m;
		assert(a);
		return a == 1 ? 1 : int(m - ll(minv(m, a)) * ll(m) / a);
	}
public:
	modnum() : v(0) {}
	modnum(ll v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
	explicit operator int() const { return v; }
	friend std::ostream& operator << (std::ostream& out, const modnum& n) { return out << int(n); }
	friend std::istream& operator >> (std::istream& in, modnum& n) { ll v_; in >> v_; n = modnum(v_); return in; }
 
	friend bool operator == (const modnum& a, const modnum& b) { return a.v == b.v; }
	friend bool operator != (const modnum& a, const modnum& b) { return a.v != b.v; }
 
	modnum inv() const {
		modnum res;
		res.v = minv(v, MOD);
		return res;
	}
	modnum neg() const {
		modnum res;
		res.v = v ? MOD-v : 0;
		return res;
	}
 
	modnum operator- () const {
		return neg();
	}
	modnum operator+ () const {
		return modnum(*this);
	}
 
	modnum& operator ++ () {
		v ++;
		if (v == MOD) v = 0;
		return *this;
	}
	modnum& operator -- () {
		if (v == 0) v = MOD;
		v --;
		return *this;
	}
	modnum& operator += (const modnum& o) {
		v += o.v;
		if (v >= MOD) v -= MOD;
		return *this;
	}
	modnum& operator -= (const modnum& o) {
		v -= o.v;
		if (v < 0) v += MOD;
		return *this;
	}
	modnum& operator *= (const modnum& o) {
		v = int(ll(v) * ll(o.v) % MOD);
		return *this;
	}
	modnum& operator /= (const modnum& o) {
		return *this *= o.inv();
	}
 
	friend modnum operator ++ (modnum& a, int) { modnum r = a; ++a; return r; }
	friend modnum operator -- (modnum& a, int) { modnum r = a; --a; return r; }
	friend modnum operator + (const modnum& a, const modnum& b) { return modnum(a) += b; }
	friend modnum operator - (const modnum& a, const modnum& b) { return modnum(a) -= b; }
	friend modnum operator * (const modnum& a, const modnum& b) { return modnum(a) *= b; }
	friend modnum operator / (const modnum& a, const modnum& b) { return modnum(a) /= b; }
};
 
template <typename T> T pow(T a, long long b) {
	assert(b >= 0);
	T r = 1; while (b) { if (b & 1) r *= a; b >>= 1; a *= a; } return r;
}

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
	pairnum operator-() const {
		return pairnum(-t, -u);
	}
	pairnum operator+() const {
		return pairnum(+t, +u);
	}
	pairnum& operator += (const pairnum &o) {
		t += o.t;
		u += o.u;
		return *this;
	}
	pairnum& operator -= (const pairnum &o) {
		t -= o.t;
		u -= o.u;
		return *this;
	}
	pairnum &operator*=(const pairnum &o) {
		t *= o.t;
		u *= o.u;
		return *this;
	}
	pairnum &operator/=(const pairnum &o) {
		t /= o.t;
		u /= o.u;
		return *this;
	}
	friend pairnum operator+(const pairnum& a, const pairnum& b) { return pairnum(a) += b; }
	friend pairnum operator-(const pairnum& a, const pairnum& b) { return pairnum(a) -= b; }
	friend pairnum operator*(const pairnum& a, const pairnum& b) { return pairnum(a) *= b; }
	friend pairnum operator/(const pairnum& a, const pairnum& b) { return pairnum(a) /= b; }
};


using num = modnum<int(1e9)+7>;
using hsh = pairnum<num, num>;
const int MOD = int(1e9)+7;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> MULT_DIST(0.1 * MOD, 0.9 * MOD); // not too close to ends
hsh base(MULT_DIST(rng), MULT_DIST(rng));

hsh inv_base(1/base.t, 1/base.u);

struct hash_t {
    string s; 
    vector<hsh> base_pow, inv_base_pow, pref;
    hash_t(string &_s) : base_pow(_s.size()), inv_base_pow(_s.size()), 
	pref(s.size()+10) {
		s = _s;
		base_pow[0] = inv_base_pow[0] = 1;
		for (int i = 1; i < s.size(); ++i) {
			base_pow[i] = base_pow[i-1] * base;
			inv_base_pow[i] = inv_base_pow[i-1] * inv_base;
		}
		for (int i = 0; i < s.size(); ++i)
			pref[i+1] = pref[i] + base_pow[i] * (s[i] -'a' + 1);
	}
	hsh get_inv_hash(int a, int b) {
		assert(a <= b);
		return inv_base_pow[a] * (pref[b+1] - pref[a]);
	}
	hsh get_hash(int a, int b) {
		assert(a <= b);
		return pref[b] - pref[a] * base_pow[b - a];
	}
    int lcp(hash_t &b) {
        int left = 0, right = min(s.size(), (b.s).size());
        while (left < right) {
            int mid = (left + right + 1)/2;
            if (pref[mid] == b.pref[mid]) left = mid;
            else right = mid-1;
        }
        return left;
    }
};

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    string s, t;
    cin >> s >> t;
    s = ' ' + s;
    t = ' ' + t;
    hash_t h(s), p(t);   
    
    cout << h.get_range(3, 6) << ' ' << p.get_range(2, 5) << '\n';
    
}