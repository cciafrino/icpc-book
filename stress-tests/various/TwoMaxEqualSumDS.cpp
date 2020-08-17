#include<bits/stdc++.h>

using namespace std;

#include "../../content/various/TwoMaxEqualSumDS.h"


#define MAX 15

int pot[MAX+2];
void pre(){
	pot[0] = 1;
	for(int i=1;i<=MAX+1;i++)
		pot[i] = pot[i-1]*3;

}

int main(){
	pre();
	srand(time(0));
	for(int t=1; t<=20; t++){
		int n = rand()%MAX+1;
		vector<int> v(n);
		for(int i=0;i<n;i++)
			v[i] = rand()%100+1;
		
		int smax = 0;
		for(int m=0;m<pot[n];m++){
			vector<int> tk(n);
			int mask = m;
			int i=0;
			while(mask){
				tk[i++] = mask%3;
				mask/=3;
			}
			int s1=0, s2=0;
			for(i=0;i<n;i++){
				if(tk[i]==1)s1+=v[i];
				if(tk[i]==2)s2+=v[i];
			}
			if(s1 == s2) smax = max(smax, s1);		
		}
		auto ans = twoMaxEqualSumDS(v);
		
		int s1=0, s2=0;
		for(int i=0;i<n;i++){
			if(ans.second[i]==1)s1+=v[i];
			if(ans.second[i]==2)s2+=v[i];
		}

		assert(ans.first == s1);
		assert(ans.first == s2);
		assert(smax == ans.first);
		
	
	}
	return 0;
}
