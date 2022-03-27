/**
 * Author: ?
 * License: CC0
 * Description:  Detect loop in a list. Consider using mod template to avoid overflow.
 * Status: Tested
 * Time: $O(n)$
 */
template<class F>
pair<int,int> find(int x0, F f) {
    int t = f(x0), h = f(t), mu = 0, lam = 1;
    while (t != h) t = f(t), h = f(f(h));
    h = x0;
    while (t != h) t = f(t), h = f(h), ++mu;
    h = f(t);
    while (t != h) h = f(h), ++lam;
    return {mu, lam};
}