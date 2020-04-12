/**
 * Author: Chris + BenQ
 * Date: 
 * License: 
 * Source: BenQ
 * Description: Segment tree on values instead of indices. kth return the largest number in 0-indexed interval.
 * count return the number of elements of a[i, j) that belong in [x, y].
 * Time: $O(\log(n))$
 */

template<int SZ> struct Wavelet { 
	vector<int> L[SZ], R[SZ];
	void build(vector<int> &a, int v=1, int l=0, int r=SZ-1) { 
		if (l == r) return;
		L[v] = R[v] = {0};
		vector<int> A[2]; int m = l + (r-l)/2;
		for(auto &t : a) {
			A[t>m].push_back(t);
			L[v].push_back(A[0].size()), R[v].push_back(A[1].size());
		}
		build(A[0],2*v,l,m), build(A[1],2*v+1,m+1,r);
	}
	int kth(int i,int j,int k,int v=1,int l=0,int r=SZ-1) { // [i, j)!!
		if (l == r) return l;
		int m = l + (r - l)/2, t = L[v][j]-L[v][i];
		if (t >= k) return kth(L[v][i], L[v][j],k,2*v,l,m);
		return kth(R[v][i], R[v][j],k-t,2*v+1,m+1,r);
	}
	int count(int i,int j,int x, int y, int v=1,int l=0,int r=SZ-1) { 
		if (y < l || r < x) return 0; //count(i, j, x, y) retorna o numero de elementos 
		if (x <= l && r <= y) return j - i; // de a[i, j) que pertencem a [x, y]
		int m = l + (r - l)/2;
		return count(L[v][i], L[v][j], x, y, 2*v, l, m) + count(i-L[v][i], j-L[v][j], x, y, 2*v+1, m+1, r);
	}
};
