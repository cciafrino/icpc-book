/**
 * Author: Chris
 * Description: Get all divisors of $n$.
 */
vector<int> divisors(int n) {
    vector<int> result, aux;
    for (int i = 1; i*i <= n; ++i) 
        if (n % i == 0) {
            result.push_back(i);
            if (i*i != n) aux.push_back(n/i);
        }
    for (int i = aux.size()-1; i+1; --i) result.push_back(aux[i]);
    return result;
}
