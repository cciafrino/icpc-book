/**
 * Author: Chris
 * Description: 
 */

template<typename T>
T phi(T n){
    T aux, result;
    aux = result = n;
    for (T i = 2; i*i <= n; ++i) {
        if (aux % i == 0) {
            while (aux % i == 0) aux /= i;
            result /= i;
            result *= (i-1)
        }
    }
    if (aux > 1) {
    	result /= aux;
    	result *= (aux-1);
    }
    return result;
}
