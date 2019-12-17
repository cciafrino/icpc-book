#include<bits/stdc++.h>
using namespace std;

using lint = long long;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<int> v(n+1); //original array
	for (int i = 0; i < n; ++i) cin >> v[i];

	vector<int> tree(2*n+1), lazy(2*n+1);
    
    for (int i = 0; i < n; ++i) tree[i+n] = v[i];
	for (int i = n-1; i >= 0; --i) tree[i] = tree[2*i] + tree[2*i+1];
	for (int i = 0; i < 2*n; ++i) lazy[i] = 0;
	int q;
	cin >> q;
	for (int i = 0; i < q; ++i) {
		int op;
		cin >> op;
		if (op) {
			int lx, rx, delta;
			cin >> lx >> rx >> delta;
			int x = lx + n, y = rx + n;
			int len = 1;
			for (lx += n, rx += n; lx <= rx; ++lx /= 2, --rx /= 2, len *= 2) {
				if (lx%2 == 1) {
					tree[lx] += delta * len;
					if (lx < n) lazy[lx] += delta;
				}
				if (rx%2 == 0) {
					tree[rx] += delta * len;
					if (rx < n) lazy[rx] += delta;
				}
			}
			for (int sz = 2; x /= 2; sz *= 2) {
				tree[x] = tree[2*x] + tree[2*x+1];
				tree[x] += lazy[x] * len;
			}
			for (int sz = 2; y /= 2; sz *= 2) {
				tree[y] = tree[2*y] + tree[2*y+1];
				tree[y] += lazy[y] * len;
			}

		}
		else {
			lint result = 0;
			int a, b ;
			cin >> a >> b;
			a += n; b += n;
			int lg = ceil(log2(*max_element(v.begin(), v.end())));
			int len = 1 << (lg-1);
			for (int h = lg; h; h--, len /= 2) {
				int p = a >> h;
				if (lazy[p]) {
					tree[2*p] += lazy[p] * len;
					if (2*p <= n) lazy[2*p] += lazy[p];
					tree[2*p+1] += lazy[p] * len;
					if (2*p+1 <= n) lazy[2*p+1] += lazy[p];
					lazy[p] = 0;
				}
			}
			for (int h = lg; h; h--, len /= 2) {
				int p = b >> h;
				if (lazy[p]) {
					tree[2*p] += lazy[p] * len;
					if (2*p <= n) lazy[2*p] += lazy[p];
					tree[2*p+1] += lazy[p] * len;
					if (2*p+1 <= n) lazy[2*p+1] += lazy[p];
					lazy[p] = 0;
				}
			}
			for (;a <= b; ++a /= 2, --b /= 2) {
				if (a%2 == 1) result += tree[a];
				if (b%2 == 0) result += tree[b];
			}
			cout << result << '\n';
		}
	} 
}