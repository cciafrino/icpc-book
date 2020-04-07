/**
 * Author: Chris
 * Description: Check if an integer is a quadractic residue modulo
 * prime. If $a^{(p-1)/2} \equiv 1$ (mod $p$) has solution, otherwise
 * $a^{(p-1)/2} \equiv -1$ (mod $p$)
 */
bool EulerCriterion(int n, int p){
    if (modpow(n, (p - 1) >> 1, p) == 1) return true;
    return false;
}
