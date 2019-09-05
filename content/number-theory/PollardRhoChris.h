/**
 * Author: tfg
 * Description: 
 */

typedef unsigned long long ull;

ull f(ull x, ull c, ull n) {
	return (mod_mul(x, x, n) + c) % n;
}
 
ull PollardRho(ull n) {
	if (n % 2 == 0) return 2;
	if (prime(n)) return n;
	while (true) {
		ull c;
		do {
			c = rand() % n;
		} while(c == 0 || (c + 2) % n == 0);
		ull x = 2, y = 2, d = 1;
		ull pot = 1, lam = 1;
		do {
			if(pot == lam) {
				x = y;
				pot <<= 1;
				lam = 0;
			}
			y = f(y, c, n);
			lam++;
			d = __gcd(x >= y ? x - y : y - x, n);
		} while(d == 1);
		if(d != n) return d;
	}
}
 
vector<ull> factor(ull n) {
	vector<ull> ans, rest, times;
	if (n == 1) return ans;
	rest.push_back(n);
	times.push_back(1);
	while(!rest.empty()) {
		ull x = PollardRho(rest.back());
		if(x == rest.back()) {
			int freq = 0;
			for(int i = 0; i < rest.size(); ++i) {
				int cur_freq = 0;
				while(rest[i] % x == 0) {
					rest[i] /= x;
					cur_freq++;
				}
				freq += cur_freq * times[i];
				if(rest[i] == 1) {
					swap(rest[i], rest.back());
					swap(times[i], times.back());
					rest.pop_back();
					times.pop_back();
					i--;
				}
			}
			while(freq--) {
				ans.push_back(x);
			}
			continue;
		}
		ull e = 0;
		while(rest.back() % x == 0) {
			rest.back() /= x;
			e++;
		}
		e *= times.back();
		if(rest.back() == 1) {
			rest.pop_back();
			times.pop_back();
		}
		rest.push_back(x);
		times.push_back(e);
	}
	return ans;
}
