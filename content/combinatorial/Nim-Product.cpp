/**
 * Author: Andrew He
 * Description: Product of nimbers is associative, commutative, and distributive 
 * over addition (xor). Forms finite field of size $2^{2^k}.$ Application: 
 * Given 1D coin turning games $G_1,G_2$ $G_1\times G_2$ is the 2D coin turning 
 * game defined as follows. If turning coins at $x_1,x_2,\ldots,x_m$ is legal 
 * in $G_1$ and $y_1,y_2,\ldots,y_n$ is legal in $G_2$, then turning coins at 
 * all positions $(x_i,y_j)$ is legal assuming that the coin at $(x_m,y_n)$ 
 * goes from heads to tails. Then the grundy function $g(x,y)$ of $G_1\times G_2$ 
 * is $g_1(x)\times g_2(y).$ 
 * Source: pg 35 of https://www.fmf.uni-lj.si/~juvan/Seminar1/ferguson.pdf and
 * https://en.wikipedia.org/wiki/Nimber
 * Time: $64^2$ xors per multiplication, memorize to speed up.
 * Status: Tested on https://codeforces.com/gym/102341/problem/L
 * https://projecteuler.net/problem=459
*/
using ull = uint64_t;
ull _nimProd2[64][64];
ull nimProd2(int i, int j) {
    if (_nimProd2[i][j]) return _nimProd2[i][j];
    if ((i & j) == 0) return _nimProd2[i][j] = 1ull << (i|j);
    int a = (i&j) & -(i&j);
    return _nimProd2[i][j] = nimProd2(i ^ a, j) ^ nimProd2((i ^ a) | (a-1), (j ^ a) | (i & (a-1)));
}
void allNimProd2() {
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            if ((i & j) == 0) _nimProd2[i][j] = 1ull << (i|j);
            else {
                int a = (i&j) & -(i&j);
                _nimProd2[i][j] = _nimProd2[i ^ a][j] ^ _nimProd2[(i ^ a) | (a-1)][(j ^ a) | (i & (a-1))];
            }
        }
    }
}
ull nimProd(ull x, ull y) {
    ull res = 0;
    for (int i = 0; (x >> i) && i < 64; ++i)
        if ((x >> i) & 1)
            for (int j = 0; (y >> j) && j < 64; ++j)
                if ((y >> j) & 1) res ^= nimProd2(i, j);
    return res;
}
