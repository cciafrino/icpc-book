/**
 * Author: BenQ
 * License: CC0
 * Description:  DP eliminates overcounting
 * Status:
 * Time: 
 */
#include<ModTemplate.h>

num tot[30];
num distinct(const string &S) {
    num ans = 1; // tot[i] stands for number of distinct strings ending with character 'a'+i
    for(auto &c : S) tie(ans, tot[c-'a']) = make_pair(2*ans-tot[c-'a'],ans);
    return ans;
}

