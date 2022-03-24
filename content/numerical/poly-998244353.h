/**
 * Author: Chris, Yui Hosaka
 * Date: 2022
 * Description:
 */
#include "finite-field-fft.h"

using num = modnum<998244353U>;

FFT<998244353U, 3U, 23> fft_data;

// inv: integral, log, exp, pow
constexpr int LIM_INV = 1 << 20;  // @
num invs[LIM_INV], fac[LIM_INV], invFac[LIM_INV];
struct ModIntPreparator {
  ModIntPreparator() {
    invs[1] = 1;
    for (int i = 2; i < LIM_INV; ++i) invs[i] = -((num::M / i) * invs[num::M % i]);
    fac[0] = 1;
    for (int i = 1; i < LIM_INV; ++i) fac[i] = fac[i - 1] * i;
    invFac[0] = 1;
    for (int i = 1; i < LIM_INV; ++i) invFac[i] = invFac[i - 1] * invs[i];
  }
} preparator;

template<unsigned M> struct Poly : public vector<modnum<M>> {
  Poly() {}
  explicit Poly(int n) : vector<modnum<M>>(n) {}
  Poly(const vector<modnum<M>> &vec) : vector<modnum<M>>(vec) {}
  Poly(std::initializer_list<modnum<M>> il) : vector<modnum<M>>(il) {}
  int size() const { return vector<modnum<M>>::size(); }
  num at(long long k) const { return (0 <= k && k < size()) ? (*this)[k] : 0U; }
  int ord() const { for (int i = 0; i < size(); ++i) if ((*this)[i]) return i; return -1; }
  int deg() const { for (int i = size(); --i >= 0;) if ((*this)[i]) return i; return -1; }
  Poly mod(int n) const { return Poly(vector<modnum<M>>(this->data(), this->data() + min(n, size()))); }
  friend std::ostream &operator<<(std::ostream &os, const Poly &fs) {
    os << "[";
    for (int i = 0; i < fs.size(); ++i) { if (i > 0) os << ", "; os << fs[i]; }
    return os << "]";
  }
  Poly &operator+=(const Poly &fs) {
    if (size() < fs.size()) this->resize(fs.size());
    for (int i = 0; i < fs.size(); ++i) (*this)[i] += fs[i];
    return *this;
  }
  Poly &operator-=(const Poly &fs) {
    if (size() < fs.size()) this->resize(fs.size());
    for (int i = 0; i < fs.size(); ++i) (*this)[i] -= fs[i];
    return *this;
  }
  Poly &operator*=(const Poly &fs) {
    if (this->empty() || fs.empty()) return *this = {};
    *this = fft_data.convolve(*this, fs);
    return *this;
  }
  Poly &operator*=(const num &a) {
    for (int i = 0; i < size(); ++i) (*this)[i] *= a;
    return *this;
  }
  Poly &operator/=(const num &a) {
    const num b = a.inv();
    for (int i = 0; i < size(); ++i) (*this)[i] *= b;
    return *this;
  }
  Poly &operator/=(const Poly &fs) {
      auto ps = fs;
      if (size() < ps.size()) return *this = {};
      int s = int(size()) - int(ps.size()) + 1;
      int nn = 1; for (; nn < s; nn <<= 1) {}
      reverse(this->begin(), this->end());
      reverse(ps.begin(), ps.end());
      this->resize(nn); ps.resize(nn);
      ps = ps.inv();
      *this = *this * ps;
      this->resize(s); reverse(this->begin(), this->end());
      return *this;
  }
  Poly &operator%=(const Poly& fs) {
      if (size() >= fs.size()) {
          Poly Q = (*this / fs) * fs;
          this->resize(fs.size() - 1);
          for (int x = 0; x < int(size()); ++x) (*this)[x] -= Q[x];
      }
      while (size() && this->back() == 0) this->pop_back();
      return *this;
  }
  Poly inv() const {
    if (this->empty()) return {};
    Poly b({(*this)[0].inv()}), fs;
    b.reserve(2 * int(this->size()));
    while (b.size() < this->size()) {
        int len = 2 * int(b.size());
        b.resize(2 * len, 0);
        if (int(fs.size()) < 2 * len) fs.resize(2 * len, 0);
        fill(fs.begin(), fs.begin() + 2 * len, 0);
        copy(this->begin(), this->begin() + min(len, int(this->size())), fs.begin());
        fft_data.fft(b);
        fft_data.fft(fs);
        for (int x = 0; x < 2*len; ++x) b[x] = b[x] * (2 - fs[x] * b[x]);
        fft_data.inverse_fft(b);
        b.resize(len);
    }
    b.resize(this->size()); return b;
  }
  Poly differential() const {
      if (this->empty()) return {};
      Poly f(max(size() - 1, 1));
      for (int x = 1; x < size(); ++x) f[x - 1] = x * (*this)[x];
      return f;
  }
  Poly integral() const {
      if (this->empty()) return {};
      Poly f(size() + 1);
      for (int x = 0; x < size(); ++x) f[x + 1] = invs[x + 1] * (*this)[x];
      return f;
  }
  Poly log() const {
      if (this->empty()) return {};
      Poly f = (differential() * inv()).integral();
      f.resize(size()); return f;
  }
  Poly exp() const {
      Poly f = {1};
      if (this->empty()) return f;
      while (f.size() < size()) {
          int len = min(f.size() * 2, size());
          f.resize(len);
          Poly d(len);
          copy(this->begin(), this->begin() + len, d.begin());
          Poly g = d - f.log();
          g[0] += 1;
          f *= g;
          f.resize(len);
      }
      return f;
  }
  Poly pow(int N) const {
      Poly b(size());
      if (N == 0) { b[0] = 1; return b; }
      int p = 0;
      while (p < size() && (*this)[p] == 0) ++p;
      if (1LL * N * p >= size()) return b;
      num mu = ((*this)[p]).pow(N), di = ((*this)[p]).inv();
      Poly c(size() - N*p);
      for (int x = 0; x < int(c.size()); ++x) {
          c[x] = (*this)[x + p] * di;
      }
      c = c.log();
      for (auto& val : c) val *= N;
      c = c.exp();
      for (int x = 0; x < int(c.size()); ++x) {
          b[x + N*p] = c[x] * mu;
      }
      return b;
  }
  Poly operator+() const { return *this; }
  Poly operator-() const {
    Poly fs(size());
    for (int i = 0; i < size(); ++i) fs[i] = -(*this)[i];
    return fs;
  }
  Poly operator+(const Poly &fs) const { return (Poly(*this) += fs); }
  Poly operator-(const Poly &fs) const { return (Poly(*this) -= fs); }
  Poly operator*(const Poly &fs) const { return (Poly(*this) *= fs); }
  Poly operator%(const Poly &fs) const { return (Poly(*this) %= fs); }
  Poly operator/(const Poly &fs) const { return (Poly(*this) /= fs); }
  Poly operator*(const num &a) const { return (Poly(*this) *= a); }
  Poly operator/(const num &a) const { return (Poly(*this) /= a); }
  friend Poly operator*(const num &a, const Poly &fs) { return fs * a; }

  // multipoint evaluation/interpolation
  friend Poly eval(const Poly& fs, const Poly& qs) {
      int N = int(qs.size());
      if (N == 0) return {};
      vector<Poly> up(2 * N);
      for (int x = 0; x < N; ++x) {
          up[x + N] = Poly({0-qs[x], 1});
      }
      for (int x = N-1; x >= 1; --x) {
          up[x] = up[2 * x] * up[2 * x + 1];
      }
      vector<Poly> down(2 * N);
      down[1] = fs % up[1];
      for (int x = 2; x < 2*N; ++x) {
          down[x] = down[x / 2] % up[x];
      }
      Poly y(N); 
      for (int x = 0; x < N; ++x) {
          y[x] = (down[x + N].empty() ? 0 : down[x + N][0]);
      }
      return y;
  }
  friend Poly interpolate(const Poly& fs, const Poly& qs) {
      int N = int(fs.size());
      vector<Poly> up(2 * N);
      for (int x = 0; x < N; ++x) {
          up[x + N] = Poly({0-fs[x], 1});
      }
      for (int x = N-1; x >= 1; --x) {
          up[x] = up[2 * x] * up[2 * x + 1];
      }
      Poly E = eval(up[1].differential(), fs);
      vector<Poly> down(2 * N);
      for (int x = 0; x < N; ++x) {
          down[x + N] = Poly({qs[x] * E[x].inv()});
      }
      for (int x = N-1; x >= 1; --x) {
          down[x] = down[2*x] * up[2*x+1] + down[2*x+1] * up[2*x];
      }
      return down[1];
  }
  friend Poly convolve_all(const vector<Poly>& fs, int l, int r) {
      if (r - l == 1) return fs[l];
      else {
          int md = (l + r) / 2;
          return convolve_all(fs, l, md) * convolve_all(fs, md, r);
      }
  }
  Poly bernoulli(int N) const {
      Poly fs(N);
      fs[1] = 1;
      fs = fs.exp(); 
      copy(fs.begin()+1, fs.end(), fs.begin());
      fs = fs.inv();
      for (int x = 0; x < N; ++x) fs[x] *= fac[x];
      return fs;
  }
  // x(x - 1)(x - 2)...(x - N + 1)
  Poly stirling_first(int N) const {
      if (N == 0) return {1};
      vector<Poly> P(N);
      for (int x = 0; x < N; ++x) P[x] = {-x, 1};
      return convolve_all(P, 0, N);
  }
  Poly stirling_second(int N) const {
      if (N == 0) return {1};
      Poly P(N), Q(N);
      for (int x = 0; x < N; ++x) {
          P[x] = (x & 1 ? -1 : 1) * invFac[x];
          Q[x] = num(x).pow(N) * invFac[x];
      }
      return P * Q;
  }
};
