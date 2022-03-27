/**
 * Author: Chris
 * Description: Count the number of inversions to make an array sorted. Merge sort has another approach.
 * Time: $O(nlog(n))$
 */
#include"../data-structures/fenwick-tree.h"

FT<lint> bit(n);    
lint inv = 0;
for (int i = n-1; i >= 0; --i) {
    inv += bit.query(values[i]); // careful with the interval 
    bit.update(values[i], 1);    // [0, x) or [0, x] ?
}
