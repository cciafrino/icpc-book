/**
 * Author: LeticiaFCS
 * Date: 2020-04-01
 * License: CC0
 * Description: Generate all free polyominoes with n squares.
 * Takes less than a sec for $n \geq 10$, around 2s for n=10
 * and around 6s for n=11
 * Status: Tested on URI 1712
 */

int diri[] = { 0, 1, 0,-1};
int dirj[] = { 1, 0,-1, 0};

typedef pair<int,int> pii;
vector<vector<pii>> poly [LIM];
void findPoly(int n){
	poly[1] = {{{0 , 0}}};
	for(int i = 2 ; i <= n; i++) {
		set<vector<pii>> cur_om;
		for(auto &om : poly[i-1]) {
			pii mini = om[0];
			for(auto &p : om)
				for(int d = 0; d < 4; d++) {
					int x = p.st + diri[d];
					int y = p.nd + dirj[d];
					if(!binary_search(om.begin(), om.end(), pii(x,y))) {
						auto m = min(mini, {x, y});
						pii new_cell(x - m.st, y - m.nd);
						bool new_in = false;
						vector<pii> norm;
						for(auto &pn : om) {
							pii cur(pn.st - m.st, pn.nd - m.nd);
							if(cur > new_cell && !new_in){
								new_in = true;
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
