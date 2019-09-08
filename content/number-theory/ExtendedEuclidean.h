/**
 * Author: Chris
 * Description: Finds the Greatest Common Divisor to the integers $a$ and $b$. Euclid also finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$. If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
 */
 
template<typename T>
T egcd(T a, T b, T &x, T &y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    T p = b / a;    
    T g = egcd(b - p * a, a, y, x);
    x -= y * p;
    return g;
}
