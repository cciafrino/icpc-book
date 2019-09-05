/**
 * Author: Stjepan Glavina
 * Source: https://github.com/stjepang/snippets/blob/master/min_rotation.cpp
 * Description: Finds the lexicographically smallest rotation of a string.
 * Time: O(N)
 * Status: Fuzz-tested
 * Usage:
 *  rotate(v.begin(), v.begin()+min_rotation(v), v.end());
 */
#pragma once

int min_rotation(string s) { /// start-hash
	int a=0, N=s.size(); s += s;
	for(int b = 0; b < N; ++b) for(int i =0; i < N; ++i) {
		if (a+i == b || s[a+i] < s[b+i]) {b += max(0, i-1); break;}
		if (s[a+i] > s[b+i]) { a = b; break; }
	}
	return a;
} /// end-hash
