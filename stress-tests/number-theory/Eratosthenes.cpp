#include "../utilities/template.h"

const int LIM = 90000;
bitset<LIM> isPrime;

vi eratosthenes() {
	const int S = (int)round(sqrt(LIM)), R = LIM / 2;
	vi pr = {2}, sieve(S+1); pr.reserve(int(LIM/log(LIM)*1.1));
	vector<pii> cp;
	for (int i = 3; i <= S; i += 2) if (!sieve[i]) {
		cp.push_back({i, i * i / 2});
		for (int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
	}
	for (int L = 1; L <= R; L += S) {
		array<bool, S> block{};
		for (auto &[p, idx] : cp)
			for (int i=idx; i < S+L; idx = (i+=p)) block[i-L] = 1;
		rep(i,0,min(S, R - L))
			if (!block[i]) pr.push_back((L + i) * 2 + 1);
	}
	for (int i : pr) isPrime[i] = 1;
	return pr;
}

vector<int> run_sieve(int n) {
	vector<int> lp(n+1), primes; primes.reserve(n+1);
	int p;
	iota(lp.begin(), lp.end(), 0);
	for (int i = 2; i <= n; ++i){
		if (lp[i] == i)  primes.push_back(i);
		for (int j = 0; j < primes.size() && (p = primes[j]*i) <= n; ++j) {
			lp[p] = primes[j];
			if (i % primes[j] == 0) { break; }
		} 
	}
	return primes;
}

vector<int> run_sieve2(int N) {
	vector<int> pfac(N+1);
	vector<int> primes; primes.reserve(N+1);
	vector<int> mu(N+1, -1); mu[1] = 1;
	vector<int> phi(N+1); phi[1] = 1;
	for (int i = 2; i <= N; ++i) {
		if (!pfac[i]) { 
			pfac[i] = i; primes.push_back(i); 
			phi[i] = i - 1;
		}
		for (int p : primes) {
			if (p > N/i) break;
			pfac[p * i] = p;
			mu[p * i] *= mu[i];
			phi[p * i] = phi[i] * phi[p];
			if (p == pfac[i]) {
				mu[p * i] = 0;
				phi[p * i] = phi[i] * p;
				break;
			}
		}
	}
	return phi;
}

void test(int NUM_CASES) {
	for (int lim=1; lim<=500; lim++) {
		auto pr = run_sieve(NUM_CASES);
		auto pr2 = run_sieve2(NUM_CASES);
		assert(pr == pr2);
	}
	cout<<"Tests passed!"<<endl;
}

void measure_mine(int NUM_CASES) {
	const auto timerBegin = std::chrono::high_resolution_clock::now();
	for (int lim=1; lim<=500; lim++) {
		auto pr2 = run_sieve2(NUM_CASES);
	}
	const auto timerEnd = std::chrono::high_resolution_clock::now();
	cerr << "Mine: " << std::chrono::duration_cast<std::chrono::milliseconds>(
      timerEnd - timerBegin).count() << " msec" << endl;
}

void measure_chinese(int NUM_CASES) {
	const auto timerBegin = std::chrono::high_resolution_clock::now();
	for (int lim=1; lim<=500; lim++) {
		auto pr = run_sieve(NUM_CASES);
	}
	const auto timerEnd = std::chrono::high_resolution_clock::now();
	cerr << "Chinese: " << std::chrono::duration_cast<std::chrono::milliseconds>(
      timerEnd - timerBegin).count() << " msec" << endl;
}

void measure_kactl(int NUM_CASES) {
	const auto timerBegin = std::chrono::high_resolution_clock::now();
	for (int lim=1; lim<=500; lim++) {
		auto pr = eratosthenes();
	}
	const auto timerEnd = std::chrono::high_resolution_clock::now();
	cerr << "KACTL: " << std::chrono::duration_cast<std::chrono::milliseconds>(
      timerEnd - timerBegin).count() << " msec" << endl;
}
int main() {
	//test(1000);
	auto pr = run_sieve2(10000);
	for (int i = 0; i <= 20; ++i) {
		cout << pr[i] << ' ';
	}
	cout << endl;
	//measure_mine(90000);
	//measure_chinese(90000);
	//measure_kactl(90000);
}
