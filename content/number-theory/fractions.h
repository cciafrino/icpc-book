/**
 * Author: BenQ (adapted by LeticiaFCS)
 * Date: 
 * License: 
 * Source: 
 * Description: Template that helps deal with fractions.
 */
template<typename num = long long>
struct frac { /// start-hash
    num n, d;
    frac() : n(0), d(1) { }
    static num fgcd( const num &a, const num &b ){ return gcd(a, b); }
    frac(num _n, num _d = 1): n(_n), d(_d){
        num g = fgcd(n, d); n /= g, d /= g;
        if (d < 0) n *= -1, d *= -1;
        assert(d != 0);
    }
    friend frac abs(frac F) { return frac(abs(F.n),F.d); }
    friend bool operator<(const frac& l, const frac& r) { return l.n * r.d < r.n * l.d; }
    friend bool operator==(const frac& l, const frac& r) { return l.n == r.n && l.d == r.d; }
    friend bool operator!=(const frac& l, const frac& r) { return !(l == r); }
    friend frac operator+(const frac& l, const frac& r) { 
    	num g = fgcd(l.d, r.d);
    	return frac( r.d / g * l.n + l.d / g * r.n, l.d / g * r.d);
    }
    friend frac operator-(const frac& l, const frac& r) { 
    	num g = fgcd(l.d, r.d);
    	return frac( r.d / g * l.n - l.d / g * r.n, l.d / g * r.d);
    }
    friend frac operator*(const frac& l, const frac& r) { return frac(l.n * r.n, l.d * r.d); }
    friend frac operator/(const frac& l, const frac& r) { return l * frac(r.d, r.n); }
    friend frac& operator+=(frac& l, const frac& r) { return l = l+r; }
    friend frac& operator-=(frac& l, const frac& r) { return l = l-r; }
    template<class T> friend frac& operator*=(frac& l, const T& r) { return l = l*r; }
    template<class T> friend frac& operator/=(frac& l, const T& r) { return l = l/r; }
    friend ostream& operator<<(ostream& strm, const frac& a) {
        strm << a.n << "/" << a.d;
        return strm;
    }
};


