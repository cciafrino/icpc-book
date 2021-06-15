/**
 * Author: Chris
 * Description: Get all divisors of $n$.
 */
vector<int> divisors(int N) {
    vector<int> result;
    for (int d = 1; d*d <= N; ++d) 
        if (N % d == 0) {
            result.push_back(d);
            if (N > d*d) result.push_back(N/d);
        }
    return result;
}
