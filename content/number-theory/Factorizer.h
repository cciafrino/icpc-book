/**
 * Author: Chris
 * Description: 
 */
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<typename T> struct Factorizer {
	const int N = 1010000;
	T C, mut, A[1001000];
	vector<T> factors, exp, lp, d;
	vector<int> prime, p;
	int cnt, l, psize, how_many;
	Factorizer(int _n) : psize(_n), factors(10010), prime(N),
		p(N), exp(100), lp(100) { run_sieve(); }
	inline T mul(T a, T b, T m) {
		if (m <= 1000000000) return a * b % m;
		else if (m <= 1000000000000ll) return (((a*(b>>20)%m)<<20)+(a*(b&((1<<20)-1))))%m;
		else {
			T x = (T)floor(a*(long double)b/m+0.5);
			T ret = (a*b - x*m) % m;
			if (ret < 0) ret += m;
			return ret;
		}
	}
	void run_sieve(){
		int i, j, tot, t1;
		for (i = 1; i <= psize; ++i) p[i] = i;
		for (i = 2, tot = 0; i <= psize; ++i){
			if (p[i] == i) prime[++tot] = i;
			for (j = 1; j <= tot && (t1 = prime[j] * i) <= psize; ++j){
				p[t1] = prime[j];
				if (i % prime[j] == 0) break;
			} 
		}
	}
	T modpow(T a, T n, T m) {
		T ans = 1;
		for (;n; n >>= 1) {
			if (n&1) ans = mul(ans, a, m);
			a = mul(a, a, m);
		}
		return ans;
	}
	bool witness(T a, T n) {
		int t = 0;
		T u = n-1;
		for (; ~u&1; u >>= 1) t += 1;
		T x = modpow(a, u, n), y=0;
		for (; t; t--) {
			y = mul(x, x, n);
			if (y == 1 && x != 1 && x != n-1) return 1;
			x = y;
		}
		return y != 1;
	}
	bool miller(T n) {
		if (n < 2) return 0;
		if (n <= psize) return p[n] == n;
		if (~n&1) return 0;
		for (int j = 0; j < 8; ++j) if (witness(rng()%(n-1)+1,n)) return 0;
		return 1;
	}
	T gcd(T a, T b) {
		T ret = 1;
		while (a) {
			if ((~a&1) && (~b&1)) ret <<= 1, a >>= 1, b >>= 1;
			else if (~a&1) a >>= 1; else if (~b&1) b >>= 1;
			else {
				if (a < b) swap(a, b);
				a -= b;
			}
		}
		return ret * b;
	}
	T rho(T n) {
		while (1) {
			T X = rng() % n, Y, Z, Q = 1, *lY = A, *lX = lY;
			int tmp = 20;
			C = rng() % 10 + 3;
			X = mul(X, X, n) + C; *(lY++) = X; ++lX;
			Y = mul(X, X, n) + C; *(lY++) = Y;
			while (X != Y) {
				T t = X - Y + n;
				Z = mul(Q, t, n);
				if (Z == 0) return gcd(Q, n);
				tmp--;
				if (tmp == 0) {
					tmp = 20;
					Z = gcd(Z, n);
					if (Z != 1 && Z != n) return Z;
				}
				Q = Z;
				Y = *(lY++) = mul(Y,Y,n) + C;
				Y = *(lY++) = mul(Y,Y,n) + C;
				X = *(lX++);
			}
		}
	}
	void get_factors(T n) {
		for (int i = 0; i < cnt; ++i) {
			if (n % factors[i] == 0) n /= factors[i], factors[cnt++] = factors[i];}
		if (n <= psize) {
			for (;n != 1; n /= p[n]) factors[cnt++] = p[n];
			return;
		}
		if (miller(n)) factors[cnt++] = n;
		else {
			T x = rho(n);
			get_factors(x); get_factors(n/x);
		}
	}
	void dfs(T x, int depth) {
		if (depth == how_many) d.push_back(x);
		else {
			dfs(x, 1 + depth);
			for (int i = 1; i <= exp[depth]; ++i) 
				dfs(x *= lp[depth], 1 + depth);
		}
	}
	void norm() {
		sort(factors.begin(), factors.begin() + cnt);
		how_many = 0;
		for(int i = 0; i < cnt; ++i) 
			if (i == 0 || factors[i] != factors[i-1]) 
				lp[how_many] = factors[i], exp[how_many++] = 1;
			else ++exp[how_many-1];
	}
	vector<T> getd() {
		d.clear();
		dfs(1, 0);
		return d;
	}
	vector<T> factorize(T n) {
		cnt = 0;
		get_factors(n); norm();
		return getd();
	}
	vector<pair<T,T>> factorsPow(T n) {
		cnt = 0;
		get_factors(n);
		norm();
		vector<pair<T,T>> D;
		for(int i = 0; i < how_many; ++i) D.push_back({lp[i], exp[i]});
		return D;
	}
	bool is_primitive(T a, T m) {
		assert(miller(m));
		vector<pair<T, T>> D = factorsPow(m-1);
		for(int i = 0; i < (int)D.size(); ++i) 
			if (modpow(a,(m-1)/D[i].first, m) == 1) return false;
		return true;
	}
};