/**
 * Author: Chris
 * Description: Lucas theorem
 * Time: $O(log_p(n)\textt{mod_inverse()})$
 * Source: 
 */
#include<ModTemplate.h>
#include<nCr.h>

num lucas(lint n, lint m) {
	num c = 1;
	while (n || m) {
		lint x = n % MOD, y = m % MOD;
		if (x < y) return 0;
		c = c * ncr(x, y);
		n /= MOD;
		m /= MOD;
	}
	return c;
}