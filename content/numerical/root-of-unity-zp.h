/**
 * Author: Chris
 * Date: 2024
 * License: 
 * Source: 
 * Description: implementation of the root of unity in $Z_p$.
 */
#include "../number-theory/modular-arithmetic.h"
template <typename T> struct root_of_unity {};
//(MOD,3) := (M1:897581057),(M3:985661441),(M5:935329793)
using M0 = modnum<998244353U>;///start-hash
constexpr unsigned primitive_root(unsigned M) {
	if (M == 880803841U) return 26U; // (M2)
	else if (M == 943718401U) return 7U; // (M4)
	else if (M == 918552577U) return 5U; // (M6)
	else return 3U;
}
template<unsigned MOD> struct root_of_unity<modnum<MOD>> {
	static constexpr modnum<MOD> g0 = primitive_root(MOD);
	static modnum<MOD> f(int K) {
		assert((MOD-1)%K == 0); return g0.pow((MOD-1)/K);
	}
};///end-hash