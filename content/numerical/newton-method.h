/**
 * Author: ?
 * Date: 
 * License: CC0
 * Source: 
 * Description: Root find method
 * Status: tested
 */
double f(double x) { return (x*x) - 4; }
double df(double x) { return 2*x; }
double root(double x0) {
    const double eps = 1e-15;
    double x = x0;
    while (1) {
        double nx = x - (f(x)/df(x));
        if (abs(x - nx) < eps) break;
        x = nx;
    }
    return x;
}
