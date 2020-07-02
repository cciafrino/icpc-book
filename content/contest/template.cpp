#include <bits/stdc++.h>
using namespace std;

using lint = long long;
using ldouble = long double;
const double PI = static_cast<double>(acosl(-1.0));

// Retorns -1 if a < b, 0 if a = b and 1 if a > b.
int cmp_double(double a, double b = 0, double eps = 1e-9) {
    return a + eps > b ? b + eps > a ? 0 : 1 : -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

}
