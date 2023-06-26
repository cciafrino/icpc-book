/**
 * Author: Chris
 * Date: 2022
 * License: 
 * Source: own work
 * Description: Precompute factorials and inverses
 */
#include "modular-arithmetic.h"
constexpr int LIM_INV = 1 << 20;
num invs[LIM_INV], fac[LIM_INV], invFac[LIM_INV];
struct ModIntPreparator {
	ModIntPreparator() {
		invs[1] = 1;
		for (int i = 2; i < LIM_INV; ++i) invs[i] = -((num::M / i) * invs[num::M % i]);
		fac[0] = invFac[0] = 1;
		for (int i = 1; i < LIM_INV; ++i) {
			fac[i] = fac[i - 1] * i;
			invFac[i] = invFac[i - 1] * invs[i];
		}
	}
} preparator;

