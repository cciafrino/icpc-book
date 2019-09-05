/**
 * Author: Chris
 * Description: $n$ choose $r$
 */
lint ncr(lint n, lint r){
    if(r < 0 || n < 0) return 0;
    if(n < r) return 0;
    lint a = fact[n];
    a = (a * invfact[r]) % mod;
    a = (a * invfact[n-r]) % mod;
    return a;
}
