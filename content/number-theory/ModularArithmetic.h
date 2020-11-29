/**
 * Author: Chris
 * Source: hos.lyric
 * Description: Operators for modular arithmetic. 
 */

template<int M_> struct modnum {
    static constexpr int M = M_;
    using ll = long long; int x;
    constexpr modnum() : x(0) {}
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
        modnum x2 = x, xe = 1;
        for (; e; e >>= 1) {
            if (e & 1) xe *= x2;
            x2 *= x2;
        }
        return xe;
    }
    modnum inv() const {
        int a = x, b = M, y = 1, z = 0, t;
        for (;;) {
            t = a / b; a -= t * b;
            if (a == 0) {
                assert(b == 1 || b == -1);
                return modnum(b * z);
            }
            y -= t * z;
            t = b / a; b -= t * a;
            if (b == 0) {
                assert(a == 1 || a == -1);
                return modnum(a * y);
            }
            z -= t * y;
        }
    }
    friend modnum inv(const modnum& a) { return a.inv(); }
    friend modnum operator+(ll a, const modnum& b) { return (modnum(a) += b); }
    friend modnum operator-(ll a, const modnum& b) { return (modnum(a) -= b); }
    friend modnum operator*(ll a, const modnum& b) { return (modnum(a) *= b); }
    friend modnum operator/(ll a, const modnum& b) { return (modnum(a) /= b); }
    friend bool operator==(const modnum& a, const modnum& b) { a.x == b.x; }
    friend bool operator!=(const modnum& a, const modnum& b) { a.x != b.x; }
    friend ostream &operator<<(ostream& os, const modnum& a) { return os << a.x; }
    friend istream &operator>>(istream& in, modnum& n) { ll v_; in >> v_; n = modnum(v_); return in; }
};

