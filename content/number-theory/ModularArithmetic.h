/**
 * Author: Chris
 * Source: hos.lyric
 * Description: Operators for modular arithmetic. 
 */
template<int M_> struct modnum {
    static constexpr int M = M_;
    using ll = long long; int x;
    constexpr modnum() : x(0) {}
    constexpr modnum(int x_) : x(int(x_ % M)) { if (x < 0) x += M; }
    constexpr modnum(ll x_) : x(int(x_ % M)) { if (x < 0) x += M; }
    explicit operator int() const { return x; }
    modnum& operator+=(const modnum& a) { x += a.x; if (x >= M) x -= M; return *this; }
    modnum& operator-=(const modnum& a) { x -= a.x; if (x < 0) x += M; return *this; }
    modnum& operator*=(const modnum& a) { x = static_cast<int>((static_cast<ll>(x) * a.x) % M); return *this; }
    modnum& operator/=(const modnum& a) { return (*this *= a.inv()); }
    modnum operator+(const modnum& a) const { return (modnum(*this) += a); }
    modnum operator-(const modnum& a) const { return (modnum(*this) -= a); }
    modnum operator*(const modnum& a) const { return (modnum(*this) *= a); }
    modnum operator/(const modnum& a) const { return (modnum(*this) /= a); }
    modnum operator-() const { return modnum(-x); }
    modnum pow(ll e) const {
        if (e < 0) return inv().pow(-e);
        modnum a = *this, b = 1; for (; e; e /= 2) { if (e & 1) b *= a; a *= a; } return b;
    }
    modnum inv() const {
        int a = x, b = M, y = 1, z = 0;
        while (a) { 
            const int q = b / a, c = b - q * a; b = a; a = c; 
            const int w = z - static_cast<int>(q) * y; z = y; y = w; 
        } assert(b == 1); return modnum(z);
    }
    friend modnum inv(const modnum& a) { return a.inv(); }
    friend modnum operator+(ll a, const modnum& b) { return (modnum(a) += b); }
    friend modnum operator-(ll a, const modnum& b) { return (modnum(a) -= b); }
    friend modnum operator*(ll a, const modnum& b) { return (modnum(a) *= b); }
    friend modnum operator/(ll a, const modnum& b) { return (modnum(a) /= b); }
    friend bool operator==(const modnum& a, const modnum& b) { return a.x == b.x; }
    friend bool operator!=(const modnum& a, const modnum& b) { return a.x != b.x; }
    friend ostream &operator<<(ostream& os, const modnum& a) { return os << a.x; }
    friend istream &operator>>(istream& in, modnum& n) { ll v_; in >> v_; n = modnum(v_); return in; }
};
