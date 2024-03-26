/**
 * Author: Chris
 * Date: 2024
 * Description:
 */
#include "fast-fourier-transform.h"
#include "../number-theory/mod-sqrt.h"
#include "../number-theory/preparator.h"
using num = modnum<998244353U>; FFT<num> fft_data;
using P = vector<num>;
void shrink(P& P){ while(!P.empty()&&!P.back())P.pop_back();}
P& operator+=(P& a, const P& b) { ///start-hash
    int N = int(a.size()), M = int(b.size());
    a.resize(max(N, M));
    for (int i = 0; i < M; ++i) a[i] += b[i];
    return a;
}///end-hash
P operator+(const P& a,const P& b){P r=a;return r+=b;}
P& operator -=(P& a, const P& b) {///start-hash
    int N = int(a.size()), M = int(b.size());
    a.resize(max(N, M));
    for (int i = 0; i < M; ++i) a[i] -= b[i];
    return a;
}///end-hash
P operator-(const P& a,const P& b) {P r=a;return r-=b;}
P operator*(const P& a, const P& b) {
    return fft.convolve(a,b); }
P& operator*=(P& a, const P& b){ return a=a*b; }
// inverse series mod x^N
P inverse(const P& P, int N) {///start-hash
    if (P.empty()) return {};
    P b({P[0]}), ret = {P[0].inv()};
    for (int len = 1; len < N; len *= 2) {
        for (int i = len; i < min(2*len, int(P.size())); ++i) 
            b.push_back(P[i]);
        (ret *= P{2} - b * ret).resize(2*len);
    }
    ret.resize(N); return ret;
}///end-hash
P operator/(P a, P b) {///start-hash
    int s = int(a.size()) - int(b.size()) + 1;
    if (s <= 0) return {};
    reverse(a.begin(), a.end()); reverse(b.begin(), b.end());
    a.resize(s); b.resize(s); a *= inverse(std::move(b), s);
    a.resize(s); reverse(a.begin(), a.end());
    return a;
}///end-hash
P& operator/=(P& a, const P& b){return a = a / b;}
P& operator%=(P& a, const P& b) {///start-hash
    if (a.size() >= b.size()) {
		P c = (a/b) * b; a.resize(b.size()-1);
		for (int i = 0; i < int(a.size()); ++i) 
			a[i] = a[i]-c[i];
	}
	shrink(a); return a;
}///end-hash
P operator%(const P& a, const P& b) {P r=a; return r%=b;}
P deriv(P P) {///start-hash
    int N = int(P.size());
    if (N == 0) return {};
    P f(N-1);
    for (int x = 1; x < N; ++x) f[x-1] = x * P[x];
    return f;
}///end-hash
P integ(P P) {///start-hash
    int N = int(P.size());
    if (N == 0) return {};
    P f(N+1); f[1] = 1;
    for (int x = 0; x < N; ++x) f[x+1] = invs[x+1] * P[x];
    return f;
}///end-hash
// ln(P) mod x^N
P log(const P& P, int N) {///start-hash
    if (P.empty()) return {};
    P f = integ(deriv(P) * inverse(P, N));
    f.resize(N); return f;
}///end-hash
// exp(P) mod x^N
P exp(P P, int N) {///start-hash
    if (P.empty()) return {1};
    P b({P[0]+1}), ret = {1};
    for (int len = 1; len < N; len *= 2) {
        for (int i = len; i < min(2*len, int(P.size())); ++i) 
            b.push_back(P[i]);
        (ret *= (b - log(ret, 2*len))).resize(2*len);
    }
    ret.resize(N); return ret;
}///end-hash
P pow(P a, ll e, int N) {///start-hash
    P b(N);
    if (!e) { b[0] = 1; return b; }
    int p = 0;
    while (e*p < N && a[p].x == 0) ++p;
    if (1LL*e*p >= N) return b;
    num mu = a[p].pow(e), di = a[p].inv();
    int M = e*p; P c(N-M);
    for (int x = 0; x < N-M; ++x) c[x] = a[x+p] * di;
    c = log(c, N-M);
    for (auto& x : c) x = x * e;
    c = exp(c, N-M);
    for (int x = 0; x < int(c.size()); ++x) b[x+M] = c[x]*mu;
    return b;
}///end-hash
P eval(const P& a, const vector<num>& x) {///start-hash
	int N = int(x.size());
	if (!N) return {};
	vector<P> up(2*N), down(2*N);
	for (int i = 0; i < N; ++i) up[i+N]=P({0-x[i],1});
	for (int i = N-1; i >= 1; --i) up[i]=up[2*i]*up[2*i+1];
	down[1] = a % up[1];
	for (int i = 2; i < 2*N; ++i) down[i]=down[i/2]%up[i];
	vector<num> y(N);
	for (int i = 0; i < N; ++i) 
		y[i]= down[i+N].empty() ? 0 : down[i+N][0];
	return y;
}///end-hash
P interp(const vector<num>&x, const vector<num>&y){///start-hash
	int N = int(x.size()); assert(N);
	vector<P> up(2*N), down(2*N);
	for (int i = 0; i < N; ++i) up[i+N]=P({0-x[i],1});
	for (int i = N-1; i >= 1; --i) up[i]=up[2*i]*up[2*i+1];
	vector<num> a = eval(deriv(up[1]), x);
	for (int i = 0; i < N; ++i) down[i+N]=P({y[i]*a[i].inv()});
	for (int i = N-1; i >= 1; --i)
		down[i]=down[2*i]*up[2*i+1] + down[2*i+1]*up[2*i];
	return down[1];
}///end-hash
P taylor_shift(P a, int N, int K) {///start-hash
	P P(N), Q = a;
	P[0] = 1;
	for (int i = 1; i < N; ++i) P[i] += P[i-1] * K;
	for (int i = 1; i < N; ++i) P[i] *= ifact[i];
	reverse(P.begin(), P.end());
	for (int i = 1; i < N; ++i) Q[i] *= fact[i];
	P *= Q;
	for (int i = 0; i < N; ++i) P[i] = P[N-1+i] * ifact[i];
	P.resize(N);
	return P;
}///end-hash