/**
 * Author: koosaga
 * Description: For strings $a,b$ calculates LCS of $a$ with all rotations of $b$
 * Time: O(N^2)
 * Source: gs14004
 */

pair<int,int> dp[2001][4001];
string A,B;

void init() {
	for(int i = 1; i <= A.size(); ++i) 
		for(int j = 1; j <= B.size(); ++j) { // naive LCS, store where value came from
			pair<int,int>& bes = dp[i][j]; bes = {-1,-1};
			bes = max(bes,{dp[i-1][j].first,0});
			bes = max(bes,{dp[i-1][j-1].first+(A[i-1] == B[j-1]),-1});
			bes = mex(bes,{dp[i][j-1].first,-2});
			bes.second *= -1;
		}
}
void adjust(int col) { // remove col'th character of b, adjust DP
	int x = 1;
	while (x <= A.size() && dp[x][col].second == 0) x ++;
	if (x > A.size()) return; // no adjustments to dp
	pair<int,int> cur = {x,col}; dp[cur.first][cur.second].second = 0;
	while (cur.first <= A.size() && cur.second <= B.size()) { 
		// essentially decrease every dp[cur.first][y >= cur.second].first by 1
		if (cur.second < B.size() && dp[cur.first][cur.s+1].second == 2) {
			cur.second ++;
			dp[cur.first][cur.second].second = 0;
		} else if (cur.first < A.size() && cur.second < B.size() 
			&& dp[cur.first+1][cur.s+1].second == 1) {
			cur.first ++, cur.second ++;
			dp[cur.first][cur.second].second = 0;
		} else cur.first ++;
	}
}
int getAns(pair<int,int> x) {
	int lo = x.second-B.size()/2, ret = 0;
	while (x.first && x.second > lo) {
		if (dp[x.first][x.second].second == 0) x.first --;
		else if (dp[x.first][x.second].second == 1) ret ++, x.first --, x.second --;
		else x.second --;
	}
	return ret;
}
int circLCS(str a, str b) {
	A = a, B = b+b; init();
	int ans = 0;
	for(int i = 0; i < B.size(); ++i) {
		ans = max(ans,getAns({A.size(),i+B.size()}));
		adjust(i+1);
	}
	return ans;
} 