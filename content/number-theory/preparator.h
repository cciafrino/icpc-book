/**
 * Author: Chris
 * Date: 2022
 * License: 
 * Source: own work
 * Description: Precompute factorials and inverses
 */
#include "modular-arithmetic.h"
constexpr int V = 1 << 20;
num invs[V], fact[V], ifact[V];
void prepare() {
	invs[1] = 1;
	for (int i = 2; i < V; ++i) invs[i] = -((num::M / i) * invs[num::M % i]);
	fact[0] = ifact[0] = 1;
	for (int i = 1; i < V; ++i) {
		fact[i] = fact[i - 1] * i;
		ifact[i] = ifact[i - 1] * invs[i];
	}
}
