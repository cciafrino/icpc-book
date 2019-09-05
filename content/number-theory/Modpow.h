/**
 * Author: Chris
 * Description:
 */
lint modpow(lint a, lint e){
    if(e == 0) return 1;
    if(e & 1) return (a*modpow(a,e-1)) % mod;
    lint c = modpow(a, e>>1);
    return (c*c) % mod;
}
