/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source:
 * Description: This is a simple matching algorithm but should
 * be just fine in most cases. Graph $g$ should be a list of
 * neighbours of the left partition. $n$ is the size of the left
 * partition and $m$ is the size of the right partition.
 * If you want to get the matched pairs, $match[i]$ contains
 * match for vertex $i$ on the right side or $-1$ if it's not
 * matched.
 * Time: O(EV) where $E$ is the number of edges and V is the number of vertices.
 * Status: works
 * 	   Working on Kattis Bilateral Projects
 */
int x, vis[123400], b[123400], ans;

bool find_match(int u, vector<vector<int>>& edges) {
  if (vis[u] == x) return 0;
  vis[u] = x;
  for (int v : edges[u])
    if (!b[v] or find_match(b[v], edges)) return b[v]=u;
  return 0;
}

int get(int n, vector<vector<int>>& edges) {
    for(int i = 1; i <= n; ++i)
        random_shuffle(edges[i].begin(), edges[i].end());
    /*
    while(1) {
        int xx = 0;
        x++;
        for (int i = 1; i <= n; ++i) xx += find_match(i, edges);
        ans += xx;
        if (xx == 0) break;
        
    }*/
    for(int i = 1; i <= n; ++i)
        x++, ans += find_match(i, edges);//*/
    return ans;
}