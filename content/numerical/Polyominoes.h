/**
 * Author: LeticiaFCS
 * Date: 2020-04-01
 * License: CC0
 * Description: Generate all free polyominoes with at most n squares.
 * poly[x] gives the polyominoes with x squares.
 * Takes less than a sec if $n < 10$, around 2s if $n = 10$
 * and around 6s if $n = 11$.
 * Status: Tested on URI 1712 and AtCoder Beginner Contest 211 - E
 */
const int LIM = 11;
using pii = pair<int,int>;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
vector<vector<pii>> poly[LIM + 1];
void generate(int n = LIM){
	poly[1] = { { { 0 , 0 } } };
	for(int i = 2 ; i <= n; ++i) {
		set<vector<pii>> cur_om;
		for(auto &om : poly[i-1]) for(auto &p : om)
			for(int d = 0; d < 4; ++d) {
				int x = p.first + dx[d];
				int y = p.second + dy[d];
				if( ! binary_search(om.begin(), om.end(), pii(x,y)) ) {
					pii m = min(om[0], {x, y});
					pii new_cell(x - m.first, y - m.second);
					vector<pii> norm;
					bool new_in = false;
					for(pii &c : om) {
						pii cur(c.first - m.first, c.second - m.second);
						if( ! new_in && cur > new_cell ) {
							new_in = true;
							norm.push_back(new_cell);
						}
						norm.push_back(cur);
					}
					if( ! new_in ) norm.push_back(new_cell);
					cur_om.insert(norm);
				}
			}
		poly[i].assign(cur_om.begin(), cur_om.end());
	}
}
