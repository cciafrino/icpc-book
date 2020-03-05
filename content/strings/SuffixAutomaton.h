/**
 * Author: FMota
 * Date: 
 * License: Unknown
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
#pragma once

struct suffix_aut {
    vector<map<int,int>> to;
    vector<int> len, link, cnt;
    int get_node(){
        to.emplace_back();
        len.emplace_back();
        link.emplace_back();
		cnt.emplace_back();
        return (int)to.size() - 1;
    }
    int last;
    suffix_aut(){
        get_node();
        link[0] = -1;
        last = 0;
    }
    int adj(int u, int c){
        auto it = to[u].find(c);
        if(it == to[u].end()) return -1;
        return it->second;
    }
    void extend(int c){
        int cur = get_node(), p;
        len[cur] = len[last] + 1;
		cnt[cur] = 1;
        for(p = last; p != -1 && adj(p, c) == -1; p = link[p])
            to[p][c] = cur;
        if(p == -1) link[cur] = 0;
        else {
            int q = to[p][c];
            if(len[p] + 1 == len[q]) link[cur] = q;
            else {
                int cln = get_node();
                to[cln] = to[q];
                len[cln] = len[p] + 1;
                link[cln] = link[q];
                link[q] = link[cur] = cln;
                for(; p != -1 && adj(p, c) == q; p = link[p])
                    to[p][c] = cln;
            }
        }
		last = cur;
    }
	void augment(){
		int sz = len.size();
		vector<int> deg(sz, 0);
		for(int i = 1; i < sz; ++i) deg[link[i]]++;
		queue<int> q;
		for(int i = 1; i < sz; ++i) if(deg[i] == 0) q.push(i);
		while(!q.empty()){
			int u = q.front(); q.pop();
			if(link[u]){
				cnt[link[u]] += cnt[u];
				if(--deg[link[u]] == 0)
					q.push(link[u]);
			}
		}
	}
};