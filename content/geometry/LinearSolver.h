/**
 * Author: Chris
 * Date: 2019
 * License: CC0
 * Source:
 * Description: Solves the linear system (a * x + b * y = e) and (c * x + d * y = f)
 * Returns tuple (1, Point(x, y)) if solution is unique, (0, Point(0,0)) if no solution and (-1, Point(0,0)) if infinite solutions. If using integer function type, this will give wrong answer if answer is not integer.
 */
template<class T>
pair<int, Point<T>> solve_linear(T a, T b, T c, T d, T e, T f) {
	Point<T> ret;
	T det = a * d - b * c;
	if (det == 0) {
		if (b * f == d * e && a * f == c * e) return {-1, Point<T>()};
		return {0, Point<T>()};
	}
	//In case solution needs to be integer, use something like the line below.
	//assert((e * d - f * b) % det == 0 && (a * f - c * e) % det == 0);
	return {1, Point<T>((e*d - f*b) / det, (a*f - c*e) / det)};
}
