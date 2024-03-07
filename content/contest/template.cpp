#include <bits/stdc++.h>
using namespace std;
using lint = int64_t;
// Returns -1 if a < b, 0 if a = b and 1 if a > b.
int cmp_double(double a, double b = 0, double eps = 1e-9) {
    return a + eps > b ? b + eps > a ? 0 : 1 : -1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

}