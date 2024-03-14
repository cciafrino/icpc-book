#include "../utilities/template.h"
using i64 = int64_t;

#include "../../content/number-theory/modular-arithmetic.h"

const int mod = int(1e9 + 7);
using num = modnum<mod>;

ostream &operator<<(ostream& os, const num& a) { return os << a.x; }
istream &operator>>(istream& in, num& n) { ll v_; in >> v_; n = num(v_); return in; }

void unittest() {
    constexpr int MO = 1000000007;
    using num = modnum<MO>;

    // this
    assert(num(2 * MO + 10).x == 10);
    assert(num(-2 * MO + 10).x == 10);
    assert(num(num(2 * MO + 10)).x == 10);
    assert(num(num(MO * 2 + 10)).x == 10);

    // opAssign
    num a = num(10);
    (a = 2 * MO + 11) = 2 * MO + 12;
    assert(a.x == 12);

    // opOpAssign(modnum)
    a += num(MO - 10);
    assert(a.x == 2);
    (a -= num(10)) -= num(10);
    assert(a.x == MO - 18);
    a = num(100000);
    a *= num(1000000);
    assert(a.x == 100000000000LL % MO);
    a = 2;
    a /= num(3);
    static_assert((2 + 2 * MO) % 3 == 0);
    assert(a.x == (2 + 2 * MO) / 3);
    a = 3;
    a = a.pow(20);
    assert(a.x == 3486784401LL % MO);
    a = 0;
    a = a.pow(0);
    assert(a.x == 1);
    a = 2;
    a = a.pow(-2);
    static_assert((1 + MO) % 4 == 0);
    assert(a.x == (1 + MO) / 4);
    a = 10;
    a += (2 * MO + 20);
    assert(a.x == 30);
    a = 10;
    a -= (2 * MO + 20);
    assert(a.x == MO - 10);
    a = 10;
    a *= (2 * MO + 20);
    assert(a.x == 200);
    a = 10;
    a /= (2 * MO + 20);
    static_assert((1 + MO) % 2 == 0);
    assert(a.x == (1 + MO) / 2);

    // inv
    a = 10000000;
    num b = a.inv();
    assert(b.x < MO);
    assert((static_cast<long long>(a.x) * b.x) % MO == 1);

    // opUnary
    a = 0;
    assert((+a).x == 0);
    assert((-a).x == 0);
    a = MO - 1;
    assert((+a).x == MO - 1);
    assert((-a).x == 1);

    // opBinary
    assert((num(MO - 6) + num(MO - 2)).x == MO - 8);
    assert((num(MO - 6) - num(MO - 2)).x == MO - 4);
    assert((num(MO - 6) * num(MO - 2)).x == 12);
    assert((num(MO - 6) / num(MO - 2)).x == 3);
    assert((num(MO - 6) + (11LL * MO - 2)).x == MO - 8);
    assert((num(MO - 6) - (11LL * MO - 2)).x == MO - 4);
    assert((num(MO - 6) * (11LL * MO - 2)).x == 12);
    assert((num(MO - 6) / (11LL * MO - 2)).x == 3);

    // opBinaryRight
    assert(((11LL * MO - 6) + num(MO - 2)).x == MO - 8);
    assert(((11LL * MO - 6) - num(MO - 2)).x == MO - 4);
    assert(((11LL * MO - 6) * num(MO - 2)).x == 12);
    assert(((11LL * MO - 6) / num(MO - 2)).x == 3);

    // opCast
    a = MO;
    assert(!a);
    a = MO + 1;
    assert(a);

    // opEquals
    a = 2;
    b = MO + 2;
    assert(a == b);
    b = MO - 2;
    assert(a != b);

    // std::ostream &operator<<(std::ostream &os, const RMmodnum128 &a)
    a = -2;
    std::ostringstream oss;
    oss << a;
    assert(oss.str() == "1000000005");
}

// modnum::inv
void unittest_inv() {
    assert(modnum<2>(1).inv().x == 1);
    assert(modnum<3>(1).inv().x == 1);
    assert(modnum<3>(2).inv().x == 2);
    assert(modnum<4>(1).inv().x == 1);
    assert(modnum<4>(3).inv().x == 3);
    assert(modnum<10>(1).inv().x == 1);
    assert(modnum<10>(3).inv().x == 7);
    assert(modnum<10>(7).inv().x == 3);
    assert(modnum<10>(9).inv().x == 9);
    assert(modnum<998244353>(499122177).inv().x == 2);
    assert(modnum<998244353>(998244352).inv().x == 998244352);
}

// https://atcoder.jp/contests/agc045/tasks/agc045_d
void solve(const int N, const int A, const unsigned expected) {
    using num = modnum<1000000007>;
    const auto timerBegin = std::chrono::high_resolution_clock::now();

    std::vector<num> inv(N + 1), fac(N + 1), invFac(N + 1);
    inv[1] = 1;
    for (int i = 2; i <= N; ++i) {
	inv[i] = -num(num::M / i) * inv[num::M % i];
    }
    fac[0] = invFac[0] = 1;
    for (int i = 1; i <= N; ++i) {
	fac[i] = fac[i - 1] * i;
	invFac[i] = invFac[i - 1] * inv[i];
    }
    num ans;
    for (int i = 0; i <= A; ++i) {
	for (int j = 0; j < i; ++j) {
	    num tmp = ((j & 1) ? -1 : +1) * (fac[i] * invFac[j] * invFac[i - j]);
	    tmp *= fac[i - j];
	    tmp *= invFac[(i - j) - 1] * fac[(i - j) + (N - A) - 1];
	    if (i < A) {
		tmp *= invFac[(i - j) + (N - A)] * fac[(i - j) + (N - A) + (A - i - 1)];
	    }
	    ans += tmp;
	}
    }

    const auto timerEnd = std::chrono::high_resolution_clock::now();
    cerr << "N = " << N << ", A = " << A << ": expected = " << expected
	<< ", actual = " << ans << endl;
    cerr << std::chrono::duration_cast<std::chrono::milliseconds>(
	timerEnd - timerBegin).count() << " msec" << endl;
    assert(expected == ans.x);
}
void measurement() {
    solve(3, 1, 2);
    solve(3, 2, 3);
    solve(8, 4, 16776);
    solve(9999999, 4999, 90395416);
    solve(10000000, 20000, 187146217);
    // 1801 msec @ DAIVRabbit
}

void measurement_pow() {
    static constexpr int NUM_CASES = 10000000;
    using num = modnum<1000000007>;
    const auto timerBegin = std::chrono::high_resolution_clock::now();

    num ans;
    for (int i = 0; i < NUM_CASES; ++i) {
	num a;
	a.x = i;
	ans += a.pow((1LL << 60) - i);
    }

    const auto timerEnd = std::chrono::high_resolution_clock::now();
    cerr << NUM_CASES << " cases: ans = " << ans << endl;
    cerr << std::chrono::duration_cast<std::chrono::milliseconds>(
	timerEnd - timerBegin).count() << " msec" << endl;
    assert(801522223 == ans.x);
    // 2062 msec @ DAIVRabbit
}

int main() {
    unittest(); cerr << "PASSED unittest" << endl;
    unittest_inv(); cerr << "PASSED unittest_inv" << endl;
    measurement();
    measurement_pow();
    return 0;
}
