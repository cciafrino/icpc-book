#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

bool valid(vi deg) {
	int n = sz(deg);
	sort(all(deg));
	reverse(all(deg));
	int sum = 0;
	rep(i,0,n) sum += deg[i];
	if (sum & 1) return 0;
	rep(k,0,n) {
		int s = 0, t = 0;
		rep(i,0,k+1)
			s += deg[i];
		rep(i,k+1,n)
			t += min(deg[i], k + 1);
		if (s > k * (k+1) + t) return 0;
	}
	return 1;
}
using lint = long long;
bool EG(vector<int> deg) {
    sort(deg.begin(), deg.end(), greater<int>());
    int n = deg.size(), p = n-1;
    vector<lint> dp(n);
    for (int i = 0; i < n; ++i)
        dp[i] = deg[i] + (i > 0 ? dp[i-1] : 0);
    for (int k = 1; k <= n; ++k) {
        while(p >= 0 && dp[p] < k) p--;
        lint sum;
        if (p >= k-1) sum = (p-k+1)*1ll*k + dp[n-1] - dp[p];
        else sum = dp[n-1] - dp[k-1];
        if (dp[k-1] > k*(k-1ll) + sum) return false;
    }
    return dp[n-1] % 2 == 0;
}

int main() {
	rep(N,0,7) {
		vector<pii> possibleEd;
		rep(i,0,N) rep(j,0,i) possibleEd.emplace_back(i, j);
		set<vi> valids;
		rep(bi,0,(1 << sz(possibleEd))) {
			vi deg(N);
			rep(i,0,sz(possibleEd)) if (bi & (1 << i)) {
				int a, b;
				tie(a, b) = possibleEd[i];
				deg[a]++;
				deg[b]++;
			}
			assert(EG(deg));
			valids.insert(deg);
		}

		vi de(N);
		function<void(int)> rec = [&](int at) {
			if (at == N) {
				assert(EG(de) == valids.count(de));
			} else {
				rep(a,0,N) {
					de[at] = a;
					rec(at + 1);
				}
			}
		};
		rec(0);
	}
	cout << "Tests passed!" << endl;
}