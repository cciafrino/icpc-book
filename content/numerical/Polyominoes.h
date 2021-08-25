/**
 * Author: LeticiaFCS
 * Date: 2020-04-01
 * License: CC0
 * Description: Generate all free polyominoes with n squares.
 * Takes less than a sec if $n < 10$, around 2s if $n = 10$
 * and around 6s if $n = 11$.
 * Status: Tested on URI 1712
 */
using pii = pair<int,int>;
vector<int> diri = {0, 1, 0, -1};
vector<int> dirj = {1, 0, -1, 0};
vector<vector<pii>> poly[LIM];
void generate(int n){
	poly[1] = { { { 0 , 0 } } };
	for(int i = 2 ; i <= n; i++) {
		set<vector<pii>> cur_om;
		for(auto &om : poly[i-1]) {
			pii mini = om[0];
			for(auto &p : om)
				for(int d = 0; d < 4; d++) {
					int x = p.st + diri[d], y = p.nd + dirj[d];
					if(!binary_search(om.begin(), om.end(), pii(x,y))) {
						pii m = min(mini, {x, y});
						pii new_cell(x - m.st, y - m.nd);
						bool new_in = false;
						vector<pii> norm;
						for(pii &pn : om) {
							pii cur(pn.st - m.st, pn.nd - m.nd);
							if(cur > new_cell && !new_in) {
								new_in = true;
								norm.push_back(new_cell);
							}
							norm.push_back(cur);
						}
						if(!new_in) norm.push_back(new_cell);
						cur_om.insert(norm);
					}
				}
		}
		poly[i].assign(cur_om.begin(),cur_om.end());
	}
}
