#include<bits/stdc++.h>
using namespace std;

using i64 = int64_t;

const int M = 998244353;
array<i64, 50010> dp;

void prep(int N) {
    dp[0] = 1;
    for (int n = 1; n < N; ++n) {
        i64 sum = 0;
        for (int k = 0, l = 1, m = n - 1; ;) {
            sum += dp[m]; if ((m -= (k += 1)) < 0) break;
            sum += dp[m]; if ((m -= (l += 2)) < 0) break;
            sum -= dp[m]; if ((m -= (k += 1)) < 0) break;
            sum -= dp[m]; if ((m -= (l += 2)) < 0) break;
        }
        if ((sum %= M) < 0) sum += M;
        dp[n] = sum;
    }
}

void unittest() {
    assert(dp[0] == 1);
    assert(dp[1] == 1);
    assert(dp[2] == 2);
    assert(dp[3] == 3);
    assert(dp[4] == 5);
    assert(dp[5] == 7);
    assert(dp[6] == 11);
    assert(dp[7] == 15);
    assert(dp[8] == 22);
    assert(dp[9] == 30);
    assert(dp[10] == 42);
    assert(dp[11] == 56);
    assert(dp[17] == 297);
    assert(dp[34] == 12310);
    assert(dp[39] == 31185);
    assert(dp[40] == 37338);
    cout << "Tests passed!" << endl;
}

/*
  1 / (\sum_i (X^(6i^2+i) - X^(6i^2+5i+1) - X^(6i^2+7i+2) + X^(6i^2+11i+5)))
*/

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit | cin.eofbit | cin.badbit);

    mt19937 rng(48);

    prep(41);

    unittest();
}
