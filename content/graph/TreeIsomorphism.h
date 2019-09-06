/**
 * Author: ?
 * Description: Check if a two rooted or unrooted Tree are isomorphic.
 * Source: https://github.com/TimonKnigge/TCR/blob/master/snippets/graphs/rooted_tree_isomorphism.cpp
 * Time: $O(n log(n))$ 
 * Status: tested
 */

bool eqvec(const vector<int> &l, const vector<int> &r) {
   return (l.size() != r.size() ? false : equal(l.begin(), l.end(), r.begin()));
}

void radix_sort(vector<int> &lv, vector<vector<int>> &E, vector<vector<int>> &ls, vector<int> &n, vector<int> &p) {
 sort(lv.begin(), lv.end(), [&E](const lint &l, const lint &r) {
   return E[l].size() < E[r].size(); });
 int MAXL = int(E[lv.back()].size()), MAXLABEL = 0;
 vector<set<lint>> label_level(MAXL+1, set<lint>());
 for (lint u : lv) {
   for (lint v : E[u]) if (p[u] != v) ls[u].push_back(n[v]);
   sort(ls[u].begin(), ls[u].end());
   for (size_t i = 0; i < ls[u].size(); ++i)
     label_level[i].insert(ls[u][i]),
     MAXLABEL = max(MAXLABEL, int(ls[u][i]));
 }
 vector<vector<int>> buckets[2] = {vector<vector<int>>(MAXLABEL+1, vector<int>()), vector<vector<int>>(MAXLABEL+1, vector<int>())};
 int first = int(lv.size());
 for (int len = MAXL - 1, c = 1; len >= 0; --len, c = 1 - c) {
   while (first > 0 && ls[lv[first-1]].size() > (size_t)len)
     --first, buckets[c][ls[lv[first]][len]].push_back(lv[first]);
   for (lint val : label_level[len + 1]) {
     for (lint v : buckets[1-c][val])
       buckets[c][ls[v][len]].push_back(v);
     buckets[1-c][val].clear();
   }
   label_level[len + 1].clear();
 }
 for (lint val : label_level[0]) {
   for (lint v : buckets[MAXL&1][val])
     lv[first++] = v;
   buckets[MAXL&1][val].clear();
 }
 label_level[0].clear();
}

bool rooted_isomorphism(int r1, vector<vector<int>> &E1, int r2, vector<vector<int>> &E2) {
 if (E1.size() != E2.size()) return false;
 int N = int(E1.size());
 vector<vector<int>> l1, l2;
 vector<int> p1(N, -1ll), p2(N, -1ll), q1{r1}, q2{r2};
 while (!q1.empty() || !q2.empty()) {
   if (q1.size() != q2.size()) return false;
   l1.push_back(move(q1)); l2.push_back(move(q2));
   for (lint u : l1.back()) for (lint v : E1[u])
     if (p1[u] != v) q1.push_back(v), p1[v] = u;
   for (lint u : l2.back()) for (lint v : E2[u])
     if (p2[u] != v) q2.push_back(v), p2[v] = u;
 }
 vector<int> n1(N, 0ll), n2(N, 0ll);
 vector<vector<int>> ls1(N, vector<int>()), ls2(N, vector<int>());
 int L = int(l1.size());
 for (int l = L - 2; l >= 0; --l) {
   radix_sort(l1[l], E1, ls1, n1, p1);
   radix_sort(l2[l], E2, ls2, n2, p2);
   if (!eqvec(ls1[l1[l][0]], ls2[l2[l][0]])) return false;
   n1[l1[l][0]] = n2[l2[l][0]] = 0;
   for (size_t i = 1; i < l1[l].size(); ++i) {
     if (!eqvec(ls1[l1[l][i]], ls2[l2[l][i]]))
       return false;
     n1[l1[l][i]] = n2[l2[l][i]] = n1[l1[l][i-1]]
       + (eqvec(ls1[l1[l][i-1]], ls1[l1[l][i]])
         ? 0 : 1);
   }
   // For the actual isomorphism: l1[l][i] can be matched with
   // l2[l][i] if their values n1,n2 are equal. Recurse from the
   // root and just assign greedily.
   // For trees where nodes contain values: take ranges where
   // li[l][j..k] are equal and sort by value just after the radix
   // sort.
 }
 return n1[r1] == n2[r2];
}


pair<int,int> dfs(vector<vector<int>> &edges, vector<int> &parent, int v, int p) {
   parent[v] = p;
   pair<int,int> result = {0, v};
   for (int u : edges[v]) {
       if (u == p) continue;
       pair<int,int> k = dfs(edges, parent, u, v);
       result = max(result, {k.first + 1, k.second});
   }
   return result;
}

void find_center(vector<vector<int>> &edges, int &c1, int &c2) {
   vector<int> p(edges.size(), -1);
   pair<int,int> d1 = dfs(edges, p,dfs(edges,p,0, -1).second, -1);
   while(d1.first > 1) d1 = {d1.first - 2, p[d1.second]};
   c1 = d1.second;
   c2 = (d1.first == 1 ? p[d1.second] : -1);
}

bool isomorphism(vector<vector<int>> &edges1, vector<vector<int>> &edges2) {
   vector<vector<int>> c(2, vector<int>(2));
   find_center(edges1, c[0][0], c[0][1]);
   find_center(edges2, c[1][0], c[1][1]);
   if ((c[0][1] == -1) != (c[1][1] == -1)) return false;
   if (rooted_isomorphism(c[0][0], edges1, c[1][0], edges2)) return true;
   if (c[0][1] != -1 && rooted_isomorphism(c[0][1],edges1,c[1][0],edges2))
       return true;
   return false;
}

