/**
 * Author: ?
 * License: CC0
 * Description:  Detect loop in a list. Consider using mod template to avoid overflow.
 * Status: Tested
 * Time: $O(n)$
 */
lint a, b, c;

lint f(lint x) {
	return (a * x + (x % b)) % c;
}

//mu -> first ocurrence
//lambda -> cycle length
lint mu, lambda;

void Floyd(lint x0) {
    //hare -> fast pointer
    //tortoise -> slow pointer
    lint hare, tortoise;
    tortoise = f(x0);
    hare = f(f(x0));
    while(hare != tortoise) {
        tortoise = f(tortoise);
        hare = f(f(hare));
    }
    hare = x0;
    mu = 0;
    while(tortoise != hare) {
        tortoise = f(tortoise);
        hare = f(hare);
        mu++;
    }
    hare = f(tortoise);
    lambda = 1;
    while(t != h) {
        hare = f(hare);
        lambda++;
    }
}
