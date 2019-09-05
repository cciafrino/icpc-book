/**
 * Author: Letícia
 * Description: 
 */

int UpperBound(vector<int> v, int n, int x){
    int l = 1, r = n, m;
    while(l <= r){
        m=(l+r)/2; 
        if(v[m] > x && (m == 1 || v[m-1] <= x)) 
            return m;
        else if(v[m] > x) r=m-1;
        else l=m+1;
    }
    return m;
}
