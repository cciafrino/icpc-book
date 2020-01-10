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

lint modpow(lint a, lint e) {
	lint ret = 1;
	for (int i = 1; i <= e; i *= 2, a = 1LL * a * a % mod)
		if (i & e) ret = 1LL * ret * a % mod;
	return ret;
}
