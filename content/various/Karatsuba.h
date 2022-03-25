/**
 * Author: Simon Lindholm
 * Date: 2015-04-22
 * License: CC0
 * Source: me
 * Description: Faster-than-naive convolution of two sequences: $c[x] = \sum a[i]b[x-i]$.
   Uses the identity $(aX+b)(cX+d) = acX^2 + bd + ((a+c)(b+d)-ac-bd)X$.
   Doesn't handle sequences of very different length welint.
   See also FFT, under the Numerical chapter.
 * Time: O(N^{1.6})
 * Status: tested
 */
 
int size(int s) { return s > 1 ? 32-__builtin_clz(s-1) : 0; }

void karatsuba(lint *a, lint *b, lint *c, lint *t, int n) {
    int ca = 0, cb = 0; 
    for(int i = 0; i < n; ++i) ca += !!a[i], cb += !!b[i];
    if (min(ca, cb) <= 1500/n) { // few numbers to multiply
        if (ca > cb) swap(a, b);
        for(int i = 0; i < n; ++i) 
            if (a[i]) for(int j = 0; j < n; ++j) c[i+j] += a[i]*b[j];
    } 
    else {
        int h = n >> 1;
        karatsuba(a, b, c, t, h); // a0*b0
        karatsuba(a+h, b+h, c+n, t, h); // a1*b1
        for(int i = 0; i < h; ++i) a[i] += a[i+h], b[i] += b[i+h]; 
        karatsuba(a, b, t, t+n, h); // (a0+a1)*(b0+b1)
        for(int i = 0; i < h; ++i) a[i] -= a[i+h], b[i] -= b[i+h];
        for(int i = 0; i < n; ++i) t[i] -= c[i]+c[i+n];
        for(int i = 0; i < n; ++i) c[i+h] += t[i], t[i] = 0;
    }
}

vector<lint> conv(vector<lint> a, vector<lint> b) {
    int sa = a.size(), sb = b.size(); if (!sa || !sb) return {};
    int n = 1<<size(max(sa,sb)); a.resize(n), b.resize(n);
    vector<lint> c(2*n), t(2*n); 
    for(int i = 0; i < 2*n; ++i) t[i] = 0; 
    karatsuba(&a[0], &b[0], &c[0], &t[0], n);
    c.resize(sa+sb-1); return c;
}
