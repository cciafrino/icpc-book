#include<bits/stdc++.h>
using namespace std;

using lint = long long;

struct Node {
    int fail;
    vector<pair<int,int>> out; // num e tamanho do padrao
    //bool marc;  // p/ decisao
    map<char,int> trie;
	int next; // aponta para o proximo sufixo que tenha out.size > 0
};
Node tree[1000003]; // quantida maxima de nos

struct AhoCorasick {
	//bool encontrado[1005]; // quantidade maxima de padroes, p/ decisao
	int qtdNos, qtdPadroes;
	vector<vector<int>> result;
	AhoCorasick() { // Construtor para inicializar
		result.resize(0);
	    tree[0].fail = -1;
	    tree[0].trie.clear();
	    tree[0].out.clear();
	    tree[0].next = -1;
	    qtdNos = 1;
	    qtdPadroes = 0;
	    //tree[0].marc = false; // p/ decisao
	    //memset(encontrado, false, sizeof(encontrado)); // p/ decisao
	}
	// Funcao para adicionar um padrao
	void add(string &pat) {
		vector<int> v;
		result.push_back(v);
	    int no = 0, len = 0;
	    for (int i = 0; i < pat.size(); i++, len++) {
	        if (tree[no].trie.find(pat[i]) == tree[no].trie.end()) {
	            tree[qtdNos].trie.clear(); tree[qtdNos].out.clear();
	            //tree[qtdNos].marc = false; // p/ decisao
	            tree[no].trie[pat[i]] = qtdNos;
	            no = qtdNos++;
	        } else no = tree[no].trie[pat[i]];
	    }
	    tree[no].out.push_back({qtdPadroes++,len});
	}

	// Ativar Aho-corasick, ajustando funcoes de falha
	void activate() {
	    int no,v,f,w;
	    queue<int> bfs;
	    for (auto  it = tree[0].trie.begin();
	       it != tree[0].trie.end() ; it++) {
	        tree[no = it->second].fail = 0;
	        tree[no].next = tree[0].out.size() ? 0 : -1;
	        bfs.push(no);
	    }
	    while (!bfs.empty()) {
	        no = bfs.front(); bfs.pop();
	        for (auto it = tree[no].trie.begin();
	             it != tree[no].trie.end(); it++) {
	            char c = it->first;
	            v = it->second;
	            bfs.push(v);
	            f = tree[no].fail;
	            while (tree[f].trie.find(c) == tree[f].trie.end()) {
	                if (f == 0) { tree[0].trie[c] = 0; break; }
	                f = tree[f].fail;
	            }
	            w = tree[f].trie[c];
	            tree[v].fail = w;
	            tree[v].next = tree[w].out.size() ? w : tree[w].next;
	        }
	    }
	}
	// Buscar padroes no aho-corasik
	void search_all(string &text) {
	    int v, no = 0;
	    for (int i = 0; i < text[i]; i++) {
	        while (tree[no].trie.find(text[i]) == tree[no].trie.end()) {
	            if (no == 0) { tree[0].trie[text[i]] = 0; break; }
	            no = tree[no].fail;
	        }
	        v = no = tree[no].trie[text[i]];
	        // marcar os encontrados
	        while (v != -1 /* && !tree[v].marc */ ) { // p/ decisao
	            //tree[v].marc = true; // p/ decisao: nao continua a trie
	            for (int k = 0 ; k < tree[v].out.size() ; k++) {
	                //encontrado[tree[v].out[k].first] = true; // p/ decisao
	                result[tree[v].out[k].first].push_back(i-tree[v].out[k].second+1);
	                printf("Padrao %d na posicao %d\n", tree[v].out[k].first,
	                       i-tree[v].out[k].second+1);
	            }
	            v = tree[v].next;
	        }
	    }
	}
};
int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    AhoCorasick ac;
    for (int i = 0; i < n; ++i) {
    	string s;
    	cin >> s;
    	ac.add(s);
    }
    ac.activate();
    string t;
    cin >> t;
    ac.search_all(t);
      
}