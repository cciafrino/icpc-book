/**
 * Author: Chris
 * Source: https://codeforces.com/blog/entry/53925
 * Description: This lemma let us exploit the fact tha the sequence (harmonic on integer division) has at most $2 \sqrt{N}$ distinct elements, so we can 
 * iterate through every possible value of $\lfloor{\frac{N}{i} \rfloor}$, using the fact that the greatest integer $j$ satisfying 
 * $\lfloor\frac{N}{i}\rfloor = \lfloor{\frac{N}{j}} \rfloor$ is $\lfloor{\frac{N}{\lfloor{\frac{N}{i}\rfloor}}}\rfloor$. This one computes the $\sum_{i=1}^{N} \lfloor{\frac{N}{i}}\rfloor i$.
 *
 * Time: $O(\sqrt N)$
 * Status: Tested on CSES and Project Euler
 */

int res = 0;
for (int a = 1, b; a <= N; a = b + 1) {
    b = N / (N / a);
    // for all i in [a, b] since they all have the same quotient (N / a)
    // and there are (b - a + 1) elements in this interval
    int l = b - a + 1, r = a + b; // l * r / 2 = sum(i, j)
    if (l & 1) r /= 2;
    else l /= 2;
    res += l * r * (N / a);
} 
