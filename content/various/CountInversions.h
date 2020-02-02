/**
 * Author: Chris
 * Description: Count the number of inversions to make an array sorted. Merge sort has another approach.
 * Time: $O(n*log(n))$
 */
#include<FenwickTree.h>

FT<int, 10010> bit;    
int inv = 0;
for (int i = n-1; i >= 0; --i) {
    inv += bit.sum(values[i]); // careful with the interval 
    bit.update(values[i], 1);    // [0, x) or [0, x] ?
}

