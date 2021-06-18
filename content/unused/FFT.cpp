typedef unsigned int uint;
typedef long double ldouble;

template<typename T, typename U, typename B> struct ModularFFT {
  inline T ifmod(U v, T mod) { return v >= (U)mod ? v - mod : v; }
  T pow(T x, U y, T p) {
    T ret = 1, x2p = x;
    while (y) {
      if (y % 2) ret = (B)ret * x2p % p;
      y /= 2; x2p = (B)x2p * x2p % p;
    }
    return ret;
  }
  vector<T> fft(vector<T> y, T mod, T gen, bool invert = false) {
    int N = y.size(); assert(N == (N&-N));
    if (N == 0) return move(y);
    vector<int> rev(N);
    for (int i = 1; i < N; ++i) {
      rev[i] = (rev[i>>1]>>1) | (i&1 ? N>>1 : 0);
      if (rev[i] < i) swap(y[i], y[rev[i]]);
    }
    assert((mod-1)%N == 0);
    T rootN = pow(gen, (mod-1)/N, mod);
    if (invert) rootN = pow(rootN, mod-2, mod);
    vector<T> rootni(N/2);
    for (int n = 2; n <= N; n *= 2) {
      T rootn = pow(rootN, N/n, mod);
      rootni[0] = 1;
      for (int i = 1; i < n/2; ++i) rootni[i] = (B)rootni[i-1] * rootn % mod;
      for (int left = 0; left != N; left += n) {
	int mid = left + n/2;
	for (int i = 0; i < n/2; ++i) {
	  T temp = (B)rootni[i] * y[mid+i] % mod;
	  y[mid+i] = ifmod((U)y[left+i] + mod - temp, mod);
	  y[left+i] = ifmod((U)y[left+i] + temp, mod);
	}
      }
    }
    if (invert) {
      T invN = pow(N, mod-2, mod);
      for (T &v : y) v = (B)v * invN % mod;
    }
    return move(y);
  }
  vector<T> convolution(vector<T> a, vector<T> b, T mod, T gen) {
    int N = a.size()+b.size()-1, N2 = nextpow2(N);
    a.resize(N2); b.resize(N2);
    vector<T> fa = fft(move(a), mod, gen), fb = fft(move(b), mod, gen), &fc = fa;
    for (int i = 0; i < N2; ++i) fc[i] = (B)fc[i] * fb[i] % mod;
    vector<T> c = fft(move(fc), mod, gen, true);
    c.resize(N); return move(c);
  }
  vector<T> self_convolution(vector<T> a, T mod, T gen) {
    int N = 2*a.size()-1, N2 = nextpow2(N);
    a.resize(N2);
    vector<T> fc = fft(move(a), mod, gen);
    for (int i = 0; i < N2; ++i) fc[i] = (B)fc[i] * fc[i] % mod;
    vector<T> c = fft(move(fc), mod, gen, true);
    c.resize(N); return move(c);
  }
  uint nextpow2(uint v) { return v ? 1 << __lg(2*v-1) : 1; }
};

//// ksun48 using mod template

using num = modnum<998244353>;
const num PRIMITIVE_ROOT = 3;
template <typename num> struct fft {
	const int L;
	const int N = (1 << L);
	using num_t = num;

	const num root;
	const num invRoot = num(1) / root;
	const num invN = num(1) / num(N);
	num roots[30+1];
	num invRoots[30+1];
	fft(int L_, num root_) : L(L_), root(root_) {
		roots[0] = root;
		invRoots[0] = invRoot;
		for (int i = 1; i <= L; i++) {
			roots[i] = roots[i-1] * roots[i-1];
			invRoots[i] = invRoots[i-1] * invRoots[i-1];
		}
		assert(roots[L] == 1);
		assert(invRoots[L] == 1);
	}

	void bitReversal(num* a) {
		for (int i = 1, j = 0; i < N-1; i++) {
			for (int k = N / 2; k > (j ^= k); k /= 2);
			if (j < i) {
				std::swap(a[j], a[i]);
			}
		}
	}

	void operator () (num* a, bool inv = false) {
		bitReversal(a);
		for (int l = 1, p = 0; l < N; l <<= 1, p++) {
			num w = inv ? invRoots[L - p - 1] : roots[L - p - 1];
			for (int k = 0; k < N; k += (2 * l)) {
				num v = 1;
				for (int i = k; i < k + l; i++, v *= w) {
					num x = a[i];
					num y = v * a[i+l];
					a[i] = x + y;
					a[i+l] = x - y;
				}
			}
		}
		if (inv) {
			for (int i = 0; i < N; i++) {
				a[i] *= invN;
			}
		}
	}
};
void conv(vector<num>& a, vector<num> b) {
	int s = int(a.size()) + int(b.size()) - 1;
	if (s <= 0) {
		a.clear();
		return;
	}
	if (s <= 200) {
		vector<num> c(s);
		for (int i = 0; i < int(a.size()); i++) {
			for (int j = 0; j < int(b.size()); j++) {
				c[i+j] += a[i] * b[j];
			}
		}
		a = c;
		return;
	}
	int L = s > 1 ? 32 - __builtin_clz(s-1) : 0, n = 1 << L;
	fft<num> f(L, PRIMITIVE_ROOT.pow((num::MOD-1) / n));
	a.resize(n); f(&a[0], false);
	b.resize(n); f(&b[0], false);
	for (int i = 0; i < n; i++) a[i] *= b[i];
	f(&a[0], true); a.resize(s);
}
