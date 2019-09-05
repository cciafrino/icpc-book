/**
 * Author: Chris
 * Description: Let $d := mdc(a, b)$. Then, there exist a pair $x$ and 
 * $y$ such that $ax + by = d$.
 */
pair<int, int> find_bezout(int x, int y) {
    if (y == 0) return bezout(1, 0);
    pair<int, int> g = find_bezout(y, x % y);
    return {g.second, g.first - (x/y) * g.second};
}
