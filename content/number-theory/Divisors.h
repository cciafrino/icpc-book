/**
 * Author: Chris
 * Description: Get all divisors of $n$.
 */
 
 vector<int> divisors(int n) {
    vector<int> ret, ret1;
    for (int i = 1; i*i <= n; ++i) {
        if (n % i == 0) {
            ret.push_back(i);
            int d = n / i;
            if (d != i) ret1.push_back(d);
        }
    }
    if (!ret1.empty()) {
        reverse(ret1.begin(), ret1.end());
        ret.insert(ret.end(), ret1.begin(), ret1.end());
    }
    return ret;
 }
