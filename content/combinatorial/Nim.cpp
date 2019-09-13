/**
 * Author: Chris
 * Date: 2018-07-06
 * License: CC0
 * Description: Sprague-grundy theorem. Example.
 */

const int MAXN = 1010;
int version;
int used[MAXN];

int mex() {
	for(int i=0; ; ++i)
		if(used[i] != version)
			return i;
}

int g[MAXN];
//remover 1, 2, 3
void grundy(){
	//Base case depends on the problem
	g[0] = 0; 
	g[1] = 1;
	g[2] = 2;
	g[3] = 3;
	//Inductive case
	for(int i = 3; i < MAXN; ++i) {
		version++;
		used[g[i-1]] = version;
		used[g[i-2]] = version;
		used[g[i-3]] = version;
		g[i] = mex();
	}
}

int main() {	
	grundy();		
	int n;
	cin >> n;
	int ans = 0;
	for(int i=0; i<n; i++){
		int x;
		cin >> x;
		ans ^= g[x];
	}
	cout << ((ans != 0) ? "First" : "Second") << endl;
	return 0;
}
