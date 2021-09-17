#include "../utilities/template.h"

template<unsigned M_> struct modnum {
    static constexpr unsigned M = M_;
    using ll = long long; using ull = unsigned long long; unsigned x;
    constexpr modnum() : x(0U) {}
    constexpr modnum(unsigned x_) : x(x_ % M) {}
    constexpr modnum(int x_) : x(((x_ %= static_cast<int>(M)) < 0) ? (x_ + static_cast<int>(M)) : x_) {}
    constexpr modnum(ull x_) : x(x_ % M) {}
    constexpr modnum(ll x_) : x(((x_ %= static_cast<ll>(M)) < 0) ? (x_ + static_cast<ll>(M)) : x_) {}
    explicit operator int() const { return x; }
    modnum& operator+=(const modnum& a) { x = ((x += a.x) >= M) ? (x - M) : x; return *this; }
    modnum& operator-=(const modnum& a) { x = ((x -= a.x) >= M) ? (x + M) : x; return *this; }
    modnum& operator*=(const modnum& a) { x = unsigned((static_cast<ull>(x) * a.x) % M); return *this; }
    modnum& operator/=(const modnum& a) { return (*this *= a.inv()); }
    modnum operator+(const modnum& a) const { return (modnum(*this) += a); }
    modnum operator-(const modnum& a) const { return (modnum(*this) -= a); }
    modnum operator*(const modnum& a) const { return (modnum(*this) *= a); }
    modnum operator/(const modnum& a) const { return (modnum(*this) /= a); }
    modnum operator+() const { return *this; }
    modnum operator-() const { modnum a; a.x = x ? (M - x) : 0U; return a; }
    modnum pow(ll e) const {
        if (e < 0) return inv().pow(-e);
        modnum x2 = x, xe = 1U;
        for (; e; e >>= 1) {
            if (e & 1) xe *= x2;
            x2 *= x2;
        }
        return xe;
    }
    modnum inv() const {
        unsigned a = x, b = M; int y = 1, z = 0;
        while (a) {
            const unsigned q = (b/a), c = (b - q*a); 
            b = a, a = c; const int w = z - static_cast<int>(q) * y;
            z = y, y = w;
        } assert(b == 1U); return modnum(z);
    }
    friend modnum inv(const modnum& a) { return a.inv(); }
    template<typename T> friend modnum operator+(T a, const modnum& b) { return (modnum(a) += b); }
    template<typename T> friend modnum operator-(T a, const modnum& b) { return (modnum(a) -= b); }
    template<typename T> friend modnum operator*(T a, const modnum& b) { return (modnum(a) *= b); }
    template<typename T> friend modnum operator/(T a, const modnum& b) { return (modnum(a) /= b); }
    friend bool operator==(const modnum& a, const modnum& b) { return a.x == b.x; }
    friend bool operator!=(const modnum& a, const modnum& b) { return a.x != b.x; }
    friend ostream &operator<<(ostream& os, const modnum& a) { return os << a.x; }
    friend istream &operator>>(istream& in, modnum& n) { ull v_; in >> v_; n = modnum(v_); return in; }
};

template<typename T, class F> T digit_dp(string& S, int K, F& L) {
	const int base = 16;
	const int len = int(S.size());

	vector<bool> w(base);
	vector<vector<T>> dp(len + 1, vector<T>(base + 1));
	
	int cnt = 0;
	for (int d = 0; d < len; ++d) {
		for (int x = 0; x <= base; ++x) {
			dp[d + 1][x] += dp[d][x] * x;
			dp[d + 1][x + 1] += dp[d][x] * (base - x);
		}
		if (d) dp[d + 1][1] += (base - 1);
		for (int x = 0; x < L(S[d]); ++x) {
			if (d == 0 && x == 0) continue;
			if (w[x]) dp[d + 1][cnt] += 1;
			else dp[d + 1][cnt + 1] += 1;
		}
		if (w[L(S[d])] == false) {
			w[L(S[d])] = true;
			cnt++;
		}
	}

	dp[len][cnt] += 1;
	
	return dp[len][K];
}


int main() {
	string N; int K; 
	
	cin >> N >> K;

	  
	auto hex_to_dec = [&](char c) -> int {
	    return ('A' <= c && c <= 'F' ? 10 + c - 'A' : c - '0');
	};

	using num = modnum<int(1e9) + 7>;

	cout << digit_dp<num>(N, K, hex_to_dec) << '\n';

	cout << "Tests passed!" << endl;
}

