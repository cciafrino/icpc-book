/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: marian's (TC) code
 * Description: Aho-Corasick tree is used for multiple pattern matching.
 * Initialize the tree with create(patterns). find(word) returns for each position
 * the index of the longest word that ends there, or -1 if none. findAll(\_, word) finds all words
 * (up to $N \sqrt N$ many if no duplicate patterns) that start at each position (shortest first).
 * Duplicate patterns are allowed; empty patterns are not.
 * To find the longest words that start at each position, reverse all input.
 * Time: create is $O(26N)$ where $N$ is the sum of length of patterns.
 * find is $O(M)$ where $M$ is the length of the word. findAll is $O(NM)$.
 * Status: lightly tested
 */
struct AhoCorasick {
	enum {alpha = 26, first = 'A'}; // change this!
	struct Node {
		// (nmatches is optional)
		int back, next[alpha]{}, pat = -1, t = -1, nmatches = 0;
		void p(int y, vector<int>& L) { t = (pat == -1 ? pat : L[t]) = y; }
	};
	vector<Node> N;
	vector<int> backp;
	void insert(string& s, int j) {
		assert(!s.empty());
		int n = 1;
		for(char c : s) {
			int& m = N[n].next[c - first];
			if (m) n = m;
			else { n = m = N.size(); N.emplace_back(); }
		}
		backp.push_back(0);
		N[n].p(j, backp);
		N[n].nmatches++;
	}
	AhoCorasick(vector<string>& pat) : N(2) {
		for(int i = 0; i < alpha; ++i) N[0].next[i] = 1;
		N[1].back = 0;
		for(int i = 0; i < pat.size(); ++i) insert(pat[i], i);

		vector<int> q(N.size()); int qe = q[0] = 1;
		for(int qi = 0; qi < qe; ++qi) {
			int n = q[qi], prev = N[n].back;
			for(int i = 0; i < alpha; ++i) {
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (!ed) ed = y;
				else {
					N[ed].back = y;
					N[ed].p(N[y].pat, backp);
					N[ed].nmatches += N[y].nmatches;
					q[qe++] = ed;
				}
			}
		}
	}
	vector<int> find(string word) {
		int n = 1;
		vector<int> res; // ll count = 0;
		for(char &c : word) {
			n = N[n].next[c - first];
			res.push_back(N[n].pat);
			// count += N[n].nmatches;
		}
		return res;
	}
	vector<vector<int>> findAll(vector<string>& pat, string word) {
		vector<int> r = find(word);
		vector<vector<int>> res(word.size());
		for(int i = 0; i < word.size(); ++i) {
			int ind = r[i];
			while (ind != -1) {
				res[i - pat[ind].size() + 1].push_back(ind);
				ind = backp[ind];
			}
		}
		return res;
	}
};
