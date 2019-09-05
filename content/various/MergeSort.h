/**
 * Author: Rodrigo Zhou
 * Description: 
 * Time: $O(n*log(n))$
 */

int n, inv;
vector<int> v, result;

void merge_sort(int lx, int rx, vector<int> &v) {
    if (lx == rx) return;
    int m = lx + (rx - lx)/2;
    merge_sort(lx, m, v);
    merge_sort(m+1, rx, v);
    int i = lx, j = m+1, k = lx;
    while(i <= m || j <= rx) {
        if (i <= m && (j > rx || v[i] < v[j])) {
            result[k++] = v[i++];
            inv += (j - k);
        }
        else result[k++] = v[j++];
    }
    for (int i = lx; i <= rx; ++i) 
        v[i] = result[i];
}
