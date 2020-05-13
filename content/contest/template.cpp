#include <bits/stdc++.h>
using namespace std;

using lint = long long;
using ldouble = long double;

const double PI = static_cast<double>(acosl(-1.0));

// Retorna -1 se a < b, 0 se a = b e 1 se a > b.
int cmp_double(double a, double b = 0, double eps = 1e-9) {
    return a + eps > b ? b + eps > a ? 0 : 1 : -1;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin.exceptions(cin.failbit);


    return 0;
}
