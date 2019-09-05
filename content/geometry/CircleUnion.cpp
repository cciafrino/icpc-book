/**
 * Author: xyz111
 * Date: 2015-09-01
 * License: CC0
 * Description: Only work with distinct circles. Also can be done with Green THeorem in 
 * $O(n^2 logn)$
 * Status: somewhat tested
 */
// 


C a[N];
int n;
double S[N];

typedef pair<double, int> PDI;
PDI A[N*2]; int LA;

void ff(int s) {
  int nn = 0;
  LA = 0;
  for (int i = 0; i < n; i ++) if (i != s) {
    double d = a[i].x.dis(a[s].x);
    if (d < a[i].r - a[s].r + eps) {nn++; continue;}
    if (d < a[s].r - a[i].r + eps || d > a[i].r + a[s].r - eps) continue;
    L p = a[s].ints_c(a[i]);
    double le = (p.x-a[s].x).tan();
    double ri = (p.y-a[s].x).tan();
    if (le < 0) le += 2*pi;
    if (ri < 0) ri += 2*pi;
    A[LA++] = mp(le, 1);
    A[LA++] = mp(ri, -1);
    if (le > ri) nn++;
  }
  A[LA++] = mp(0.0, nn);
  A[LA++] = mp(pi*2, -nn);
  sort(A, A+LA);
  int nw = 0;
  for (int i = 0; i < LA-1; i ++) {
    nw += A[i].se;
    double le = A[i].fi, ri = A[i+1].fi;
    double T = (a[s].pt(le).crs(a[s].pt(ri)) + a[s].r*a[s].r*(ri-le-sin(ri-le)))/2;
    S[nw] -= T;
    S[nw+1] += T;
  }
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i ++) a[i].get();
  for (int i = 0; i < n; i ++) ff(i);
  for (int i = 1; i <= n; i ++)
    printf ("[%d] = %.3lf\n", i, S[i]);
  return 0;
}
