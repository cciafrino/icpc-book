/**
 * Author: LeticiaFCS
 * Date: 2020-04-01
 * License: CC0
 * Description: Generate all free polyominoes with n squares 
 * Time: bad
 * Status: Tested on URI 1712
 */
int numdir = 4;
int diri[] = { 0, 1, 0,-1};
int dirj[] = { 1, 0,-1, 0};

set< set< pair<int,int> > > poly [LIM];
void findPoly(int n){
	poly[1] = { { { 0 , 0 } } };
	for(int i = 2 ; i <= n; i++)
		for(auto &om : poly[i-1]){
			pair<int,int> mini =
			{om.begin() -> st, om.begin() -> nd};
			for(auto &p: om)
				for(int d = 0; d < numdir; d++){
					int x = p.st + diri[d];
					int y = p.nd + dirj[d];
					if(! om.count({x,y}) ){
						auto m = min(mini, {x,y});
						set<pair<int,int> > norm;
						for(auto &pn:om)
							norm.insert({pn.st - m.st,
								     pn.nd - m.nd});
						norm.insert({x - m.st, y - m.nd});
						if(! poly[i].count(norm) )
							poly[i].insert(norm);
					}
				}
		}
}
