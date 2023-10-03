/**
 * Author: Lucian Bicsi, Simon Lindholm
 * Date: 2017-10-31
 * License: CC0
 * Description: Given $f$ and $N$, finds the smallest fraction $p/q \in [0, 1]$
 * such that $f(p/q)$ is true, and $p, q \le N$.
 * You may want to throw an exception from $f$ if it finds an exact solution,
 * in which case $N$ can be removed.
 * Usage: fracBS([](Frac f) { return f.p>=3*f.q; }, 10); // {1,3}
 * Time: O(\log(N))
 * Status: fuzz-tested for n <= 300
 */
struct Frac { ll p, q; };
template<class F> Frac fracBS(F f, ll N) {
	bool dir = 1, A = 1, B = 1;
	Frac left{0, 1}, right{1, 1};//right{1,0} to search (0,N]
	assert(!f(left)); assert(f(right));
	while (A || B) {
		ll adv = 0, step = 1; // move right if dir, else left
		for (int si = 0; step; (step *= 2) >>= si) {
			adv += step;
			Frac mid{left.p * adv + right.p, left.q * adv + right.q};
			if (abs(mid.p) > N || mid.q > N || dir == !f(mid)) {
				adv -= step; si = 2;
			}
		}
		right.p += left.p * adv; right.q += left.q * adv;
		dir = !dir; swap(left, right);
		A = B; B = !!adv;
	}
	return dir ? right : left;
}
