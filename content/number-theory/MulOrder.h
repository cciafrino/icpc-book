/**
 * Author: Chris
 * Description: Find the smallest integer $k$ such that $a^k$
 * (mod $m$) $= 1$. $0 < k < m$. 
 */
int mulOrder(int x, int y){
    if (__gcd(x, y) != 1) return 0;
    lint p = phi(y);
    pair<int,int> k = factorize(x);
    for (auto &t : k) 
        while(p % t.first == 0 && modpow(x, p/t.first, p) == 1) p /= t.first;
    return P;
}
