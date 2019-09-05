bool isPrime(lint n){
    if (n < 0) return isPrime(-n);
    for (lint i = 2; i*i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}
