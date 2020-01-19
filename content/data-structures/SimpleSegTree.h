/**
 * Author: Chris
 * Description: Iterative Segment Tree
 */
 
vector<int> v(1<<18); //original array
const int n = 1<<18;
vector<int> tree(2*n);

//build
for (int i = 1; i <= n; ++i) tree[i+n] = v[i];
for (int i = n; i >= 1; --i) tree[i] = tree[2*i] + tree[2*i+1];

// point update / range query
int idx = 3, delta = 8;// delta = new value, idx = position
tree[n+idx] = delta; 
for(int i = (n+idx)/2; i >= 1; i /= 2) 
    tree[i] = tree[2*i] + tree[2*i+1];
// query [l,r]
int lx = 1, rx = 9; // interval [l, r]

int result = 0;
//if (lx != rx) sum += tree[rx];
for (lx += n, rx += n; lx <= rx; lx /= 2, rx /= 2){
    if (lx%2 == 1) result += tree[lx++];
    if (rx%2 == 0) result += tree[rx--];
}

// A bit faster segtree with bitwise operators
for (M = 1; M <= n+1; M *= 2);
for (int i = 1; i <= n; ++i) tree[i+M] = v[i];
for (int i = M-1; i ; --i) tree[i] = tree[i+i] + tree[i+i+1];

int idx = 1, delta = 10;
tree[idx+M] = delta;
for (int i = (idx+M)>>1; i; i >>= 1) tree[i] = tree[i+i] + tree[i+i+1];

int res = 0;
int lx = 1, rx = 9;
for (lx += M-1, rx += M+1; lx ^ rx ^ 1; lx >>= 1, rx >>= 1) {
	if (~lx & 1) res += tree[lx^1];
	if (rx & 1) res += tree[rx^1];
}
