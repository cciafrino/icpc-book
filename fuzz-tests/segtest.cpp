#include<bits/stdc++.h>
using namespace std;

using lint = long long;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> v(n); //original array
	for (int i = 0; i < n; ++i) cin >> v[i];

	vector<int> tree(2*n);

	//build
	for (int i = 1; i <= n; ++i) tree[i+n] = v[i];
	for (int i = n-1; i >= 1; --i) tree[i] = tree[2*i] + tree[2*i+1];

	int result = 0;
	
	int q;
	cin >> q;
	for (int i = 0; i < q; ++i) {
		int k, l, r;
		result = 0;
		cin >> k >> l >> r;
		if (!k) {
			tree[n+l] = r; 
			for(int i = (n+l)/2; i >= 1; i /= 2) 
		    tree[i] = max(tree[2*i], tree[2*i+1]);
		}
		else {
			int lx = l, rx = r; // interval [l, r]
			//if (lx != rx) sum += tree[rx];
			for (lx += n, rx += n; lx <= rx; lx /= 2, rx /= 2){
			    if (lx % 2 == 1) result = max(result, tree[lx++]);
			    if (rx % 2 == 0) result = max(result, tree[rx--]);
			}
			cout << result << '\n';
		}
	}
	
        
}