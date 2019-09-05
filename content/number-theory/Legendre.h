/**
 * Author: Chris
 * Description: Given an integer $n$ and a prime number $p$, find the 
 * largest $x$ such that $p^x$ divides $n!$.
 */
int legendre(int n, int p){
    int ret = 0, prod = p;
    while (prod <= n) {
        ret += n/prod;
        prod *= p;
    }
    return ret;
}
