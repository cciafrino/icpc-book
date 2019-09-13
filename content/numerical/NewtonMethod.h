/**
 * Author: ?
 * Date: 
 * License: CC0
 * Source: Numeriska algoritmer med matlab, Gerd Eriksson, NADA, KTH
 * Description: Root find method
 * Status: tested
 */
 
double f(double x){	
	return (x*x) - 4;
}

double df(double x){	
	return 2*x;
}

double root(double x0){
    const double eps = 1E-15;
    double x = x0;
    for (;;) {
        double nx = x - (f(x)/df(x));
        if (abs(x - nx) < eps)
            break;
        x = nx;

    }
    return x;	
}
