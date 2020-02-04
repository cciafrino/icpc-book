/**
 * Author: Chris 
 * Description: Shortest Path Faster Algorithm.
 * Time: $O(E)$
 */

int s; // source node
int d[100100], f[100100], head[100100];
vector<pair<int,int>> edges[100100];
vector<int> q;
void spfa() {
    q.push_back(s);
    memset(d, 127,sizeof(d));
    memset(f,0,sizeof(f));
    f[s] = 1, d[s] = 0;
    int inf = d[s+1];
    for (int i = 0; i < q.size();++i) {
        int now=q[i];
        f[now]=0;
        for(auto u:edges[now]) {
            int cost = u.second;
            if (d[u.first] > d[now] + cost) {
                d[u.first] = d[now] + cost;
                if (!f[u.first]) {
                    f[u.first] = 1;
                    q.push_back(u.first);
                }
            }
        }
    }
}