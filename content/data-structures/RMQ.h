/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Status: Tested at Petrozavodsk
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time. 
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 */
#pragma once

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) { /// start-hash
		int N = V.size(), on = 1, depth = 1;
		while (on < V.size()) on *= 2, depth++;
		jmp.assign(depth, V);
		for (int i = 0; i < depth-1; ++i)
		    for (int j = 0; j < N; ++j)
            	jmp[i+1][j] = min(jmp[i][j],
	    		jmp[i][min(N - 1, j + (1 << i))]);
	}/// end-hash
	T query(int a, int b) { /// start-hash
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}/// end-hash
};
