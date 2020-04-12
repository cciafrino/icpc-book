/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: me
 * Description: Be careful.
 * Status:
 */
#pragma GCC optimize("Ofast") // enable all O3 optimizations
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zero-upper") //Enable AVX
#pragma GCC target("avx2")  //Enable AVX