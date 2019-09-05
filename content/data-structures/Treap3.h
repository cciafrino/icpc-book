/**
 * Author: Arthur Nascimento
 * Date: 
 * Source: 
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 */
 
const int N = ; typedef int num;
num X[N]; int en = 1, Y[N], sz[N], L[N], R[N];

void calc(int u) {
    sz[u] = sz[L[u]] + 1 + sz[R[u]];
    // code here, no recursion
}

void unlaze(int u) {
    if (!u) return;
    // code here, no recursion
}

void split_val(int u, num x, int &lx, int &rx) {
    unlaze(u); if (!u) return (void)(lx = rx = 0);
    if (X[u] <= x) {
        split_val(R[u], x, lx, rx);
        R[u] = lx;
        lx = u;
    }
    else {
        split_val(L[u], x, lx, rx);
        L[u] = rx;
        rx = u;
    }
    calc(u);
}
void split_sz(int u, int s, int &lx, int &rx) {
    unlaze(u); if (!u) return (void)(lx = rx = 0);
    if (sz[L[u]] < s) {
        split_sz(R[u], s-sz[L[u]]-1, lx, rx);
        R[u] = lx;
        lx = u;
    }
    else {
        split_sz(L[u], s, lx, rx);
        L[u] = rx;
        rx = u;
    }
    calc(u);
}

int merge(int lx, int rx) {
    unlaze(lx); unlaze(rx); if (!lx || !rx) return lx+rx;
    int u;
    if (Y[lx] > Y[rx]) {
        R[lx] = merge(R[lx], rx);
        u = lx;
    }
    else {
        L[rx] = merge(lx, L[rx]);
        u = rx;
    }
    calc(u);
    return u;
}

void build(int n = N-1) {
    for (int i = en = 1; i <= n; ++i) {
        Y[i] = i;
        sz[i] = 1;
        L[i] = R[i] = 0;
    }
    random_shuffle(Y + 1, Y + n + 1);
}




