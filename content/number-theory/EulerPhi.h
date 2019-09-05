/**
 * Author: Chris
 * Description: 
 */

lint phi(lint n){
    lint result = n;
    for (lint p = 2; p*p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}
