/**
 * Author: Chris 
 * Description: Shortest Path Faster Algorithm.
 */

int s; // source node
int dis[100100], f[100100], head[100100];
vector<pair<int,int>> edges[100100];
vector<int> q;
void spfa() {
    q.push_back(s);
    memset(dis, 127,sizeof(dis));
    memset(f,0,sizeof(f));
    f[s]=1,dis[s]=0;
    int inf=dis[s+1];
    for (int i=0;i<q.size();++i){
        int now=q[i];
        f[now]=0;
        for(auto u:edges[now]){
            int next=u.first;
            int cost=u.second;
            if (dis[next]>dis[now]+cost) {
                dis[next]=dis[now]+cost;
                if (!f[next]) {
                    f[next] = 1;
                    q.push_back(next);
                }
            }
        }
    }
}