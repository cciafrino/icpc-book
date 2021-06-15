/**
 * Author: Chris
 * Description: Get all factors of $n$.
 * Time: $O(sqrt(N)/log(N))$
 */
vector<pair<int, int>> factorize(int value) {
    vector<pair<int, int>> result;
    for (int p = 2; p*p <= value; ++p)
        if (value % p == 0) {
            int exp = 0;
            while (value % p == 0) {
                value /= p;
                ++exp;
            }
            result.emplace_back(p, exp);
        }
    if (value != 1) {
        result.emplace_back(value, 1);
        value = 1;
    }
    return result;
}

