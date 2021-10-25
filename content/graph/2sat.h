/**
 * Author: Emil Lenngren, Simon Lindholm (adapted by Felipe Chen)
 * Date: 2021-24-10
 * Source:
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem, so that an expression of the type $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$ becomes true, or reports that it is unsatisfiable.
 * Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.either(0, \tilde3); // Var 0 is true or var 3 is false
 *  ts.set_value(2); // Var 2 is true
 *  ts.at_most_one({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true
 *  ts.solve(); // Returns true iff it is solvable
 *  ts.values[0..N-1] holds the assigned values to the vars
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 */
 #include "tarjan.h"
 struct TwoSat {
	int N;
	vector<vector<int>> gr;
	vector<int> values; // 0 = false, 1 = true
	TwoSat(int n = 0) : N(n), gr(2*n) {}
	int add_var() { // (optional)
		gr.emplace_back();
		gr.emplace_back();
		return N++;
	}
	void either(int f, int j) {
		f = max(2*f, -1-2*f);
		j = max(2*j, -1-2*j);
		gr[f].push_back(j^1);
		gr[j].push_back(f^1);
	}
	void set_value(int x) { either(x, x); }
	void at_most_one(const vector<int>& li) { // (optional)
		if (int(li.size()) <= 1) return;
		int cur = ~li[0];
		for (int i = 2; i < int(li.size()); ++i) {
			int next = add_var();
			either(cur, ~li[i]);
			either(cur, next);
			either(~li[i], next);
			cur = ~next;
		}
		either(cur, ~li[1]);
	}
	bool solve() {
		scc(gr, [](const vector<int> &v){ return; } );
		values.assign(N, -1);
		for (int i = 0; i < N; ++i) if (comp[2*i] == comp[2*i+1]) return 0;
		for (int i = 0; i < N; ++i){
			if (comp[2*i] < comp[2*i+1]) values[i] = true;
			else values[i] = false;
		}
		// to minimize (to maximize change < to >) number of variables true (need graph to be symmetric if a => b then ~a => ~b) 
		/*
		vector<pair<int, int>>cnt(2*N);
		for (int i = 0; i < N; ++i){
			if (comp[2*i] < comp[2*i+1]) cnt[comp[2*i]].st++;
			else cnt[comp[2*i+1]].nd++;
		}
		for (int i = 0; i < N; ++i){
			if (comp[2*i] < comp[2*i+1]){
				if( cnt[comp[2*i]].st < cnt[comp[2*i]].nd ) values[i] = true; //change here
				else values[i] = false;
			}
			else{
				if( cnt[comp[2*i+1]].st < cnt[comp[2*i+1]].nd ) values[i] = false; //change here
				else values[i] = true;
			}
		}
		*/
		return 1;
	}
};
