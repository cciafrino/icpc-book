/**
 * Author: Chris
 * Description: Lucas theorem
 * Time: 
 * Source: 
 */

modnum lucas(lint n, lint m) {
	modnum x1 = m % MOD, x2 = m / MOD;
	modnum y1 = n % MOD, y2 = n / MOD;
	modnum ret = 1;
	if (y1 >= x1) ret = ret * ncr(y1, x1);
	else ret = 0;
	if (y2 >= x2) ret = ret * ncr(y2, x2);
	else ret = 0;
	return ret;
}