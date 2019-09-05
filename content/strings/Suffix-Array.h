/**
 * Author: chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{lcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * The input string must not contain any zero bytes.
 * Time: O(n \log n)
 * Status: fuzz-tested
 */

struct SuffixArray { 
	tor<int> sa, lcp;
	SuffixArray(tor<int> &s, int lim = 256) { 
		int n = s.size(), k = 0;
		tor<int> x(2 * n), y(2 * n), wv(n), ws(max(n, lim)), rank(n);
		sa = lcp = rank;
		for(int i=0;i<n;++i) ws[x[i] = s[i]]++;
		for(int i=1;i<lim;++i) ws[i] += ws[i - 1];
		for (int i = n; i--;) sa[--ws[x[i]]] = i;
		for (int j = 1, p = 0; p < n; j *= 2, lim = p) {
			p = 0;
			for(int i=n-j;i<n;++i) y[p++] = i;
			for(int i=0;i<n;++i) if (sa[i] >= j) y[p++] = sa[i] - j;
			for(int i=0;i<n;++i) wv[i] = x[y[i]];
			for(int i=0;i<lim;++i) ws[i] = 0;
			for(int i=0;i<n;++i) ws[wv[i]]++;
			for(int i=1;i<lim;++i) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[wv[i]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			for(int i=1;i<n;++i) {
				int a = sa[i-1], b = sa[i]; x[b] =
					y[a] == y[b] && y[a + j] == y[b + j] ? p - 1 : p++;
			}
		}
		for(int i=1;i<n;++i) rank[sa[i]] = i; 
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++) ;
	}
};
