/**
 * Author: 
 * Description: Finds the minimum spanning arborescence from the root. (any more notes?)
 */
#define N 110000
#define M 110000
#define inf 2000000000

struct edg {
    int u, v;
    int cost;
} E[M], E_copy[M];

int In[N], ID[N], vis[N], pre[N];

// edges pointed from root. 
int Directed_MST(int root, int NV, int NE) { 
	for (int i = 0; i < NE; i++)
		E_copy[i] = E[i];
    int ret = 0;
    int u, v;
    while (true) {/// start-hash
        for (int i = 0; i < NV; ++i) In[i] = inf;
        for (int i = 0; i < NE; ++i) {
            u = E_copy[i].u;
            v = E_copy[i].v;
            if(E_copy[i].cost < In[v] && u != v) {
                In[v] = E_copy[i].cost;
                pre[v] = u;
            }
        }
        for (int i = 0; i < NV; ++i) {
            if(i == root)   continue;
            if(In[i] == inf)    return -1; // no solution
        }

        int cnt = 0;
        for (int i = 0; i < NV; ++i) {
        	ID[i] = -1;
        	vis[i] = -1;
        }
        In[root] = 0;

        for (int i = 0; i < NV; ++i) {
            ret += In[i];
            int v = i;
            while(vis[v] != i && ID[v] == -1 && v != root) {
                vis[v] = i;
                v = pre[v];
            }
            if(v != root && ID[v] == -1) {
                for(u = pre[v]; u != v; u = pre[u]) {
                    ID[u] = cnt;
                }
                ID[v] = cnt++;
            }
        }
        if(cnt == 0)    break;
        for (int i = 0; i < NV; ++i) {
            if(ID[i] == -1) ID[i] = cnt++;
        }
        for (int i = 0; i < NE; ++i) {
            v = E_copy[i].v;
            E_copy[i].u = ID[E_copy[i].u];
            E_copy[i].v = ID[E_copy[i].v];
            if(E_copy[i].u != E_copy[i].v) {
                E_copy[i].cost -= In[v];
            }
        }
        NV = cnt;
        root = ID[root];
    }
    return ret;
}/// end-hash

