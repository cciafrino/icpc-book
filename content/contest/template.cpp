#include <bits/stdc++.h>
using namespace std;

using lint = long long;
using ldouble = long double;

const double PI = 2 * acos(0.0);

// Retorna -1 se a < b, 0 se a = b e 1 se a > b.
int cmp_double(double a, double b = 0, double eps = 1e-9) {
    return a + eps > b ? b + eps > a ? 0 : 1 : -1;
}

string read_string() {
    char *str;
    scanf("%ms", &str);
    string result(str);
    free(str);
    return result;
}

inline int read() {
    ret = 0;
    while((ch = getchar()) >= '0')
        ret = 10 * ret + ch - '0';
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin.exceptions(cin.failbit);


    return 0;
}
