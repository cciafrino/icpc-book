/**
 * Author: Jakob Kogler, chilli, pajenegod
 * Date: 2020-04-12
 * License: CC0
 * Source:
 * Description: Prime sieve for generating all primes up to n.
 * Status: Stress-tested
 * Time: $n=1e9$ $\approx$ 1.5s
 * Details: Despite its n log log n complexity, segmented sieve is still faster
 * than other options, including bitset sieves and linear sieves. This is
 * primarily due to its low memory usage, which reduces cache misses. This
 * implementation skips even numbers.
 *
 * Benchmark can be found here: https://ideone.com/e7TbX4
 */
const int n = 1e6;
vector<int> run_sieve() {
	const int sq = round(sqrt(n)), e = n>>1, lg = int(log(n));
	vector<int> pr, sieve(sq+1); pr.reserve(int(n/lg*1.1));
	vector<array<int, 2>> cp;
	for(int i = 3; i <= sq; i += 2) if (!sieve[i]) {
		cp.push_back({i, i*i/2 - 1});
		for (int j = i*i; j <= sq; j += 2*i) sieve[j] = true;
	}
	for(int s = 1; s <= e; s += sq) {
		vector<bool> block(sq);
		for(auto &[p, id] : cp)
			for (int i = id; i < sq+s; i = (id+=p)) block[i-s] = 1;
		for(int i = 0; i < min(sq, e - s); ++i)
			if (!block[i]) pr.push_back((s + i)*2 + 1);
	};
	return pr;
}