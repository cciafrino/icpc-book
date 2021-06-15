/**
 * Author: Chris
 * Source: hos.lyric
 * Description: Operators for modular arithmetic. 
 */
template<unsigned M_> struct modnum {
    static constexpr unsigned M = M_;
    using ll = long long; using ull = unsigned long long; unsigned x;
    constexpr modnum() : x(0) {}
    constexpr modnum(unsigned x_) : x(x_ % M) { if (x < 0) x += M; }
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
        unsigned a = x, b = M; int y = 1, z = 0;
        while (a) {
            const unsigned q = (b/a), c = (b - q*a); 
            b = a, a = c; const int w = z - static_cast<int>(q) * y;
            z = y, y = w;
        } assert(b == 1); return modnum(z);
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
