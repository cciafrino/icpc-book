/**
 * Author: LeticiaFCS
 * Date: 2020-10-14
 * License: CC0
 * Description: Solves postfix (Reverse Polish) notation equation
 * to solve prefix notation equation reverse $e$ and change (i) and (ii)  
 * Time: $O(N)$
 * Status: Tested on leetcode 150, NOT tested for prefix equation
 */
template<typename T, typename P, typename F>
T postfixSolver(const vector<P> &e, const set<P> &ops, F ptot){
	vector<T> stk;
	for(auto &cur: e){
		if(ops.count(cur)){
			T c;
			//operations:
			if(cur == "+"){
				T b = stk.back(); // (i) T a = stk.back();
				stk.pop_back();
				T a = stk.back(); //(ii) T b = stk.back();
				stk.pop_back();
				c = a + b;
				// if notation is prefix:
				/*
				T a = stk.back();
				stk.pop_back();
				T b = stk.back();
				stk.pop_back();
				c = a + b;				
				*/
				
			}
			else if(cur == "NOT"){
				T a = stk.back();
				stk.pop_back();
				c = ~a;
			}
			stk.push_back(c);			
		} else 
			stk.push_back(ptot(cur));		 
	}
	return stk.back();
}
//example postfix:
vector<string> e = {"13", "14", "+", "NOT"};
int ans = postfixSolver<int>( e, {"+", "NOT"}, [](const string &s){ return stoi(s); } ); 
//example prefix:
vector<string> e = {"NOT", "+", "13", "14"};
reverse(e.begin(), e.end()); // DON'T FORGET!!!!!
int ans = postfixSolver<int>( e, {"+", "NOT"}, [](const string &s){ return stoi(s); } ); 
