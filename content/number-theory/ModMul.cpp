/**
 * Author: Chris
 * Description: Modular multiplication operation
 */
lint modMul(lint a, lint b){
    lint ret = 0;
    a %= mod;
    while (b){
        if (b & 1) ret = (ret + a) % mod;
        a = (2 * a) % mod;
        b >>= 1;
    }
    return ret;
}
