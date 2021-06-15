/**
 * Author: Chris
 * Description:  Probability of reaching N(winning)
 Variation - Loser gives a coin to the winner
 */
#include<Modpow.h>
// pmf = probability of moving forward
double random_walk(double p, int i, int n) {
    double q = 1 - p;
    if (fabs(p - q) < EPS) return 1.0 * i/n;
    return (1 - modpow(q/p, i))/(1 - modpow(q/p, n));
}
