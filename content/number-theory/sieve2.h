/**
 * Author: Chris
 */
vector<int> primes(int a){
    vector<int> pr;
    for(int p = 2; p * p <= a; p++){
        while(a % (p*p) == 0) a /= (p*p);
        if(a % p == 0){
            a /= p;
            pr.push_back(p);
        }
    }
    if(a > 1) pr.push_back(a);
    return pr;
}
