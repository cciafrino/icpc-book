/**
 * Author: BenQ + Chris
 * Date: 
 * License: 
 * Source: 
 * Description: Segment tree on values instead of indices. kth return the largest number in 0-indexed interval.
 * count return the number of elements of a[i, j) that belong in [x, y].
 * Time: $O(\log(n))$
 */

template<int SZ> struct Wavelet { 
	vector<int> L[SZ], R[SZ];
	void build(vector<int> a, int v=1, int lx=0, int rx=SZ-1) { 
		if (lx == rx) return;
		L[v] = R[v] = {0};
		vector<int> A[2]; int mid = lx + (rx-lx)/2;
		for(auto &t:a) {
			A[t>mid].pb(t);
			L[v].pb(A[0].size()), R[v].pb(A[1].size());
		}
		build(A[0],2*v,lx,mid), build(A[1],2*v+1,mid+1,rx);
	}
	int kth(int i,int j,int k,int v=1,int lx=0,int rx=SZ-1) { // [i, j)!!
		if (lx == rx) return lx;
		int mid = lx + (rx - lx)/2, t = L[v][j]-L[v][i];
		if (t >= k) return kth(L[v][i],
						L[v][j],k,2*v,lx,mid);
		return kth(R[v][i],
			R[v][j],k-t,2*v+1,mid+1,rx);
	}
	int count(int i,int j,int x, int y, int v=1,int lx=0,int rx=SZ-1) { 
		if (y < lx || rx < x) return 0; //count(i, j, x, y) retorna o numero de elementos 
		if (x <= lx && rx <= y) return j - i; // de a[i, j) que pertencem a [x, y]
		int mid = lx + (rx - lx)/2;
		return count(L[v][i], L[v][j], x, y, 2*v, lx, mid) + count(i-L[v][i], j-L[v][j], x, y, 2*v+1, mid+1, rx);
	}
};
