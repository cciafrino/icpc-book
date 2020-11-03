/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: 
 * Status: 
 * Description: Pre-compute all the Catalan numbers until $n$.
 * Usage:
 * Time: 
 */
#include<ModTemplate.h>
num catalan[1010];
catalan[0] = catalan[1] = 1;
for (int i = 2; i <= 1000; ++i) {
    catalan[i] = 0;
    for (int j = 0; j < i; ++j) 
        catalan[i] += catalan[j] * catalan[i-j-1];
}
