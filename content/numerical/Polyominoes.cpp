/**
 * Author: LeticiaFCS
 * Date: 2020-04-01
 * License: CC0
 * Description: Generate all free polyominoes with lim squares 
 * Time: bad
 * Status: Tested on URI 1712
 */

int numdir = 4;
int diri[] = {0,1,0,-1};
int dirj[] = {1,0,-1,0};

set< set<pair<int,int>> > poly [LIM];
void findPoly(int lim){
	poly[1] = {{{0,0}}};
	for(int i=2;i<=lim;i++){
		for(auto om : poly[i-1]){
			auto o = om;
			for(auto pos: om){
				for(int d=0;d<numdir;d++){
					int x=pos.st+diri[d], y=pos.nd+dirj[d];
					if(!om.count({x,y})){
						o.insert({x,y});
						int xn = (*o.begin()).first;
						int yn = (*o.begin()).second;
						set<pair<int,int>> norm;
						for(auto posn:o)
							norm.insert({posn.first-xn, posn.second-yn});
						if(!poly[i].count(norm)) poly[i].insert(norm);
						o.erase({x,y});
					}
				}
			}
		}
	}
}
