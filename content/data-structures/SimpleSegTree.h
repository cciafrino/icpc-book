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
