/**
 * Author: Chris
 * Description: Check if a the Diophantine Equation $ax + by = c$ has
 * solution.
 * Status: Tested
 */

template<typename T>
bool diophantine(T a, T b, T c, T &x, T &y, T &g) { /// start-hash
    if (a == 0 && b == 0) {
        if (c == 0) {
            x = y = g = 0;
            return true;
        }
        return false;
    }
    if (a == 0) {
        if (c % b == 0) {
            x = 0; y = c / b; g = abs(b);
            return true;
        }
        return false;
    }
    if (b == 0) {
        if (c % a == 0) {
            x = c / a; y = 0; g = abs(a);
            return true;
        }
        return false;
    }
    g = egcd<lint>(a, b, x, y);
    if (c % g != 0) return false;
    T dx = c / a;
    c -= dx * a;
    T dy = c / b;
    c -= dy * b;
    x = dx + (T) ((__int128) x * (c / g) % b);
    y = dy + (T) ((__int128) y * (c / g) % a);
    g = abs(g);
    return true; // |x|, |y| <= max(|a|, |b|, |c|) 
} 
