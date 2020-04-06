#include<bits/stdc++.h>
#define lint long long
#define st first
#define nd second
#define LIM 15

using namespace std;


int diri[] = { 0, 1, 0,-1};
int dirj[] = { 1, 0,-1, 0};

typedef pair<int,int> pii;
vector< vector<pii> > poly [LIM];
void findPoly(int n){
	poly[1] = { { { 0 , 0 } } };
	for(int i = 2 ; i <= n; i++){
		set< vector<pii> > cur_om;
		for(auto &om : poly[i-1]){
			pii mini = om[0];
			for(auto &p: om)
				for(int d = 0; d < 4; d++){
					int x = p.st + diri[d];
					int y = p.nd + dirj[d];
					if(! binary_search(om.begin(), om.end(), pii(x,y)) ){
						auto m = min(mini, {x,y});
						pii new_cell(x-m.st, y-m.nd);
						bool new_in = false;
						vector<pii> norm;						
						for(auto &pn:om){
							pii cur(pn.st - m.st, pn.nd - m.nd);
							if(cur > new_cell && !new_in){
								new_in=true;
								norm.push_back(new_cell);
							}
							norm.push_back(cur);
						}
						if(!new_in) norm.push_back(new_cell);						
						if(!cur_om.count(norm)) cur_om.insert(norm);
					}
				}
		}
		poly[i].assign(cur_om.begin(),cur_om.end());
	}
}



int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int fixed_poly [] = {0,1,2,6,19,63,216,760,2725,9910,
						 36446,135268,505861,1903890};
	
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    double time;
	
	for(int lim=1; lim <= 11; lim++){		
		auto start = chrono::high_resolution_clock::now();
		findPoly(lim);  
		auto end = chrono::high_resolution_clock::now();
		
		for(int i=1;i<lim;i++){
			assert(poly[i].size() == fixed_poly[i]);
		}
		
		time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
		time *= 1e-9;
		cout<<"lim = "<<lim<<" time = "<<time<<endl;
		
		for(int i=0;i<lim;i++)
			poly[i]=vector<vector<pii>>();
	}
	
	
	return 0;	
}






