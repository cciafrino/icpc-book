#include<bits/stdc++.h>
#define MAXN 40000
using namespace std;

#include "../../content/data-structures/range-color.h"

using lint = int64_t;

int main(){
	srand(time(NULL));
	for(int _=0; _<10; _++){
		lint l = rand()%MAXN;
		lint r = rand()%MAXN;
		tie(l, r) = minmax(l,r);
		lint maxColor = rand()%MAXN;
		lint iniColor = maxColor ? rand()%maxColor : 0;
		
		auto rangeStr = RangeColor<int, int>(l, r, maxColor, iniColor);
		
		vector<int> color(r + 1, iniColor);
		vector<int> freq(maxColor + 1);
		freq[iniColor] = (r - l + 1);
		
		int q = rand()%MAXN;
		while(q--){
			int type = rand()%3;
			if(type == 0){ // query
				int i = l + rand()%(r - l + 1);
				assert(rangeStr.query(i) == color[i]);
			}else if(type == 1){//upd
				lint a = l + rand()%(r - l + 1);
				lint b = l + rand()%(r - l + 1);
				tie(a, b) = minmax(a, b);
				int c = maxColor ? rand()%maxColor : 0;
				
				for(int i=a; i<=b; i++){
					freq[color[i]]--;
					color[i] = c;
					freq[color[i]]++;
				}
				rangeStr.upd(a, b, c);
			}else{ //countColor
				int c = maxColor ? rand()%maxColor : 0;
				assert(freq[c] == rangeStr.countColor(c));
			}
		
		}
		
		
		
	}
	
	cout << "Tests passed!" << endl;
	
	return 0;
}
