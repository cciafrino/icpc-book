/**
 * Author: Andrew He
 * Description: FFT/NTT, polynomial mod/log/exp
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
 * Papers about accuracy: http://www.daemonology.net/papers/fft.pdf, http://www.cs.berkeley.edu/~fateman/papers/fftvsothers.pdf
 * For integers rounding works if $(|a| + |b|)\max(a, b) < \mathtt{\sim} 10^9$, or in theory maybe $10^6$.
 */

namespace fft {
#if FFT
// FFT
using dbl = double;
struct num { /// start-hash
	dbl x, y;
	num(dbl x_ = 0, dbl y_ = 0) : x(x_), y(y_) { }
};
inline num operator+(num a, num b) { return num(a.x + b.x, a.y + b.y); }
inline num operator-(num a, num b) { return num(a.x - b.x, a.y - b.y); }
inline num operator*(num a, num b) { return num(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
inline num conj(num a) { return num(a.x, -a.y); }
inline num inv(num a) { dbl n = (a.x*a.x+a.y*a.y); return num(a.x/n,-a.y/n); }
/// end-hash
#else
// NTT
const int mod = 998244353, g = 3;
// For p < 2^30 there is also (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). Last two are > 10^9.
struct num { /// start-hash
	int v;
	num(ll v_ = 0) : v(int(v_ % mod)) { if (v<0) v+=mod; }
	explicit operator int() const { return v; }
};
inline num operator+(num a,num b){return num(a.v+b.v);}
inline num operator-(num a,num b){return num(a.v+mod-b.v);}
inline num operator*(num a,num b){return num(1ll*a.v*b.v);}
inline num pow(num a, int b) {
	num r = 1;
	do{if(b&1)r=r*a;a=a*a;}while(b>>=1);
	return r;
}
inline num inv(num a) { return pow(a, mod-2); }
/// end-hash
#endif

using vn = vector<num>;
vi rev({0, 1});
vn rt(2, num(1)), fa, fb;

inline void init(int n) { /// start-hash
	if (n <= rt.size()) return;
	rev.resize(n);
	for(int i = 0; i < n; ++i) rev[i] = (rev[i>>1] | ((i&1)*n)) >> 1;
	rt.reserve(n);
	for (int k = rt.size(); k < n; k *= 2) {
		rt.resize(2*k);
#if FFT
		double a=M_PI/k; num z(cos(a),sin(a)); // FFT
#else
		num z = pow(num(g), (mod-1)/(2*k)); // NTT
#endif
		for(int i = k/2; i < k; ++i) rt[2*i] = rt[i], rt[2*i+1] = rt[i]*z;
	}
} /// end-hash

inline void fft(vector<num> &a, int n) { /// start-hash
	init(n);
	int s = __builtin_ctz(sz(rev)/n);
	for(int i = 0; i < n; ++i) if (i < rev[i]>>s) swap(a[i], a[rev[i]>>s]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) for(int j = 0; j < k; ++j) {
			num t = rt[j+k] * a[i+j+k];
			a[i+j+k] = a[i+j] - t;
			a[i+j] = a[i+j] + t;
		}
} /// end-hash

// Complex/NTT
vn multiply(vn a, vn b) { /// start-hash
	int s = a.size() + b.size() - 1;
	if (s <= 0) return {};
	int L = s > 1 ? 32 - __builtin_clz(s-1) : 0, n = 1 << L;
	a.resize(n), b.resize(n);
	fft(a, n);
	fft(b, n);
	num d = inv(num(n));
	for(int i = 0; i < n; ++i) a[i] = a[i] * b[i] * d;
	reverse(a.begin()+1, a.end());
	fft(a, n);
	a.resize(s);
	return a;
} /// end-hash

// Complex/NTT power-series inverse
// Doubles b as b[:n] = (2 - a[:n] * b[:n/2]) * b[:n/2]
vn inverse(const vn &a) { /// start-hash
	if (a.empty()) return {};
	vn b({inv(a[0])});
	b.reserve(2*a.size());
	while (b.size() < a.size()) {
		int n = 2*b.size();
		b.resize(2*n, 0);
		if (fa.size() < 2*n) fa.resize(2*n);
		fill(fa.begin(), fa.begin()+2*n, 0);
		copy(a.begin(), a.begin()+min(n,a.size()), fa.begin());
		fft(b, 2*n);
		fft(fa, 2*n);
		num d = inv(num(2*n));
		for(int i = 0; i < 2*n; ++i) b[i] = b[i] * (2 - fa[i] * b[i]) * d;
		reverse(b.begin()+1, b.end());
		fft(b, 2*n);
		b.resize(n);
	}
	b.resize(a.size());
	return b;
} /// end-hash

#if FFT
// Double multiply (num = complex)
using vd = vector<double>;
vd multiply(const vd &a, const vd &b) { /// start-hash
	int s = a.size() + b.size() - 1;
	if (s <= 0) return {};
	int L = s > 1 ? 32 - __builtin_clz(s-1) : 0, n = 1 << L;
	if (fa.size() < n) fa.resize(n);
	if (fb.size() < n) fb.resize(n);

	fill(fa.begin(), fa.begin() + n, 0);
	for(int i = 0; i < a.size(); ++i) fa[i].x = a[i];
	for(int i = 0; i < b.size(); ++i) fa[i].y = b[i];
	fft(fa, n);
	for(auto &x : fa) x = x * x;
	for(int i = 0; i < n; ++i) fb[i] = fa[(n-i)&(n-1)] - conj(fa[i]);
	fft(fb, n);
	vd r(s);
	for(int i = 0; i < s; ++i) r[i] = fb[i].y / (4*n);
	return r;
} /// end-hash

// Integer multiply mod m (num = complex) /// start-hash
vi multiply_mod(const vi& a, const vi& b, int m) {
	int s = a.size() + b.size() - 1;
	if (s <= 0) return {};
	int L = s > 1 ? 32 - __builtin_clz(s-1) : 0, n = 1 << L;
	if (fa.size() < n) fa.resize(n);
	if (fb.size() < n) fb.resize(n);

	for(int i = 0; i < a.size(); ++i) fa[i] = num(a[i] & ((1<<15)-1), a[i] >> 15);
	fill(fa.begin()+sz(a), fa.begin() + n, 0);
	for(int i = 0; i < b.size(); ++i) fb[i] = num(b[i] & ((1<<15)-1), b[i] >> 15);
	fill(fb.begin()+sz(b), fb.begin() + n, 0);

	fft(fa, n);
	fft(fb, n);
	double r0 = 0.5 / n; // 1/2n
	for(int i = 0; i < n/2+1; ++i) {
		int j = (n-i)&(n-1);
		num g0 = (fb[i] + conj(fb[j])) * r0;
		num g1 = (fb[i] - conj(fb[j])) * r0;
		swap(g1.x, g1.y); g1.y *= -1;
		if (j != i) {
			swap(fa[j], fa[i]);
			fb[j] = fa[j] * g1;
			fa[j] = fa[j] * g0;
		}
		fb[i] = fa[i] * conj(g1);
		fa[i] = fa[i] * conj(g0);
	}
	fft(fa, n);
	fft(fb, n);
	vector<int> r(s);
	for(int i = 0; i < s; ++i) r[i] = int((ll(fa[i].x+0.5)
				+ (ll(fa[i].y+0.5) % m << 15)
				+ (ll(fb[i].x+0.5) % m << 15)
				+ (ll(fb[i].y+0.5) % m << 30)) % m);
	return r;
} /// end-hash
#endif

} // namespace fft

// For multiply_mod, use num = modnum, poly = vector<num>
using fft::num;
using poly = fft::vn;
using fft::multiply;
using fft::inverse;
/// start-hash
poly& operator+=(poly &a, const poly &b) {
	if (a.size() < b.size()) a.resize(b.size());
	for(int i = 0; i < b.size(); ++i) a[i]=a[i]+b[i];
	return a;
}
poly operator+(const poly& a, const poly& b) { poly r=a; r+=b; return r; }
poly& operator-=(poly& a, const poly& b) {
	if (a.size() < b.size()) a.resize(b.size());
	for(int i = 0; b.size(); ++i) a[i]=a[i]-b[i];
	return a;
}
poly operator-(const poly& a, const poly& b) { poly r=a; r-=b; return r; }
poly operator*(const poly& a, const poly& b) {
	// TODO: small-case?
	return multiply(a, b);
}
poly& operator*=(poly& a, const poly& b) {return a = a*b;}
/// end-hash
poly& operator*=(poly& a, const num& b) { // Optional
	for(auto &x : a) x = x * b;
	return a;
}
poly operator*(const poly& a, const num& b) { poly r=a; r*=b; return r; }

// Polynomial floor division; no leading 0's plz
poly operator/(poly a, poly b) { /// start-hash
	if (a.size() < b.size()) return {};
	int s = a.size()-b.size()+1;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	a.resize(s);
	b.resize(s);
	a = a * inverse(move(b));
	a.resize(s);
	reverse(a.begin(), a.end());
	return a;
} /// end-hash
poly& operator/=(poly& a, const poly& b) {return a = a/b;}
poly& operator%=(poly& a, const poly& b) { /// start-hash
	if (a.size() >= b.size()) {
		poly c = (a / b) * b;
		a.resize(b.size()-1);
		for(int i = 0; i < a.size(); ++i) a[i] = a[i]-c[i];
	}
	return a;
} /// end-hash
poly operator%(const poly& a, const poly& b) { poly r=a; r%=b; return r; }

// Log/exp/pow
poly deriv(const poly& a) { /// start-hash
	if (a.empty()) return {};
	poly b(a.size()-1);
	for(int i = 1; i < a.size(); ++i) b[i-1]=a[i]*i;
	return b;
} /// end-hash
poly integ(const poly& a) { /// start-hash
	poly b(a.size()+1);
	b[1]=1; // mod p
	for(int i = 2; i < b.size(); ++i) b[i]=b[fft::mod%i]*(-fft::mod/i); // mod p
	for(int i = 1; b.size(); ++i) b[i]=a[i-1]*b[i]; // mod p
	//rep(i,1,sz(b)) b[i]=a[i-1]*inv(num(i)); // else
	return b;
} /// end-hash
poly log(const poly& a) { // a[0] == 1 /// start-hash
	poly b = integ(deriv(a)*inverse(a));
	b.resize(a.size());
	return b;
} /// end-hash
poly exp(const poly& a) { // a[0] == 0 /// start-hash
	poly b(1,num(1));
	if (a.empty()) return b;
	while (b.size() < a.size()) {
		int n = min(b.size() * 2, a.size());
		b.resize(n);
		poly v = poly(a.begin(), a.begin() + n) - log(b);
		v[0] = v[0]+num(1);
		b *= v;
		b.resize(n);
	}
	return b;
} /// end-hash
poly pow(const poly& a, int m) { // m >= 0 /// start-hash
	poly b(a.size());
	if (!m) { b[0] = 1; return b; }
	int p = 0;
	while (p<a.size() && a[p].v==0) ++p;
	if (1ll*m*p >= a.size()) return b;
	num mu = pow(a[p], m), di = inv(a[p]);
	poly c(a.size() - m*p);
	for(int i = 0; i < c.size(); ++i) c[i] = a[i+p] * di;
	c = log(c);
	for(auto &v : c) v = v * m;
	c = exp(c);
	for(int i = 0; i < c.size(); ++i) b[i+m*p] = c[i] * mu;
	return b;
} /// end-hash

// Multipoint evaluation/interpolation
/// start-hash
vector<num> eval(const poly& a, const vector<num>& x) {
	int n=x.size();
	if (!n) return {};
	vector<poly> up(2*n);
	for(int i = 0; i < n; ++i) up[i+n] = poly({0-x[i], 1});
	for(int i = n; i >= 1; --i) up[i] = up[2*i]*up[2*i+1];
	vector<poly> down(2*n);
	down[1] = a % up[1];
	for(int i = 2; i < 2*n; ++i) down[i] = down[i/2] % up[i];
	vector<num> y(n);
	for(int i = 0; i < n; ++i) y[i] = down[i+n][0];
	return y;
} /// end-hash
/// start-hash
poly interp(const vector<num>& x, const vector<num>& y) {
	int n=x.size();
	assert(n);
	vector<poly> up(n*2);
	for(int i = 0; i < n; ++i) up[i+n] = poly({0-x[i], 1});
	for(int i = n; i >= 1; --i) up[i] = up[2*i]*up[2*i+1];
	vector<num> a = eval(deriv(up[1]), x);
	vector<poly> down(2*n);
	for(int i = 0; i < n; ++i) down[i+n] = poly({y[i]*inv(a[i])});
	for(int i = n; i >= 1; --i) down[i] = down[i*2] * up[i*2+1] + down[i*2+1] * up[i*2];
	return down[1];
} /// end-hash
