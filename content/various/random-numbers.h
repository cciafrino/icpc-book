/**
 * Author: Chris
 * Date: 2020
 * License: CC0
 * Source: me
 * Description: An example on the usage of generator and distribution. Use shuffle instead of random shuffle.
 */
mt19937 rng(random_device{}()); 
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
shuffle(permutation.begin(), permutation.end(), rng);
uniform_int_distribution<int> uid(1, 100); //[1, 100]
uniform_real_distribution<double> urd(1, 100);
unsigned xrand() {
	static unsigned x = 314159265, y = 358979323, z = 846264338, w = 327950288;
	unsigned t = x ^ x << 11; x = y; y = z; z = w; return w = w ^ w >> 19 ^ t ^ t >> 8;
}
