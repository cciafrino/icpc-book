/**
 * Author: Chris
 * Source: 
 * Description: Solve $x^2\equiv n\mod p(0\le a<p)$ where $p$ is prime in $O(\log p)$. 
 * If $p > n$, factorize $p$ and solve each of $x^2\equiv n\mod p_i$ \forall $i$.
 * Status: Tested
 * Time:
 */
void mul(lint &a1, lint &b1, lint a2, lint b2, lint w, lint p) {
	lint t1 = (a1*a2 + b1*b2 % p*w), t2 = (a1*b2 + a2*b1);
	a1 = t1 % p, b1 = t2 % p;
}
int Pow(lint a, lint w, lint b, lint p) {
	lint res1=1, res2=0, c1=a, c2=1;
	for (;b;b>>=1) { if (b&1) mul(res1,res2,c1,c2,w,p); mul(c1,c2,c1,c2,w,p); }
	return res1;
}
int quadratic(lint n, int p) {
	lint a, r = 0; n %= p;
	if (p == 2) return -1;
	if (n == 0) return 0;
	if (modpow(n, p/2, p) != 1) return -1;
	do a = rng() % (p-1)+1; while((modpow(a*a-n, p/2, p)-1) % p == 0);
	r = Pow(a, (a*a-n) % p, (p+1)/2, p);
	if (r < 0) r += p;
	assert((r*r-n) % p == 0);
	return r;
}
