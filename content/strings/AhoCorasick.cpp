
/**
 * Author: Maurício Collares (Adapted)
 * Description: String searching algorithm that matches all strings simultaneously. To use with stl string: (char *)stringname.c\_str()
 */

struct Node {
    int fail;
    vector<pair<int,int>> out; // num e tamanho do padrao
    //bool marc;  // p/ decisao
    map<char,int> link;
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
	    tree[0].link.clear();
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
	        if (tree[no].link.find(pat[i]) == tree[no].link.end()) {
	            tree[qtdNos].link.clear(); tree[qtdNos].out.clear();
	            //tree[qtdNos].marc = false; // p/ decisao
	            tree[no].link[pat[i]] = qtdNos;
	            no = qtdNos++;
	        } else no = tree[no].link[pat[i]];
	    }
	    tree[no].out.push_back({qtdPadroes++,len});
	}
	// Ativar Aho-corasick, ajustando funcoes de falha
	void activate() {
	    int no,v,f,w;
	    vector<int> bfs;
	    for (auto  it = tree[0].link.begin();
	       it != tree[0].link.end() ; it++) {
	        tree[no = it->second].fail = 0;
	        tree[no].next = tree[0].out.size() ? 0 : -1;
	        bfs.push_back(no);
	    }
	    for(int i = 0; i < bfs.size(); ++i) {
	        no = bfs[i]; 
	        for (auto it = tree[no].link.begin();
	             it != tree[no].link.end(); it++) {
	            char c = it->first;
	            v = it->second;
	            bfs.push_back(v);
	            f = tree[no].fail;
	            while (tree[f].link.find(c) == tree[f].link.end()) {
	                if (f == 0) { tree[0].link[c] = 0; break; }
	                f = tree[f].fail;
	            }
	            w = tree[f].link[c];
	            tree[v].fail = w;
	            tree[v].next = tree[w].out.size() ? w : tree[w].next;
	        }
	    }
	}
	// Buscar padroes no aho-corasik
	void search_all(string &text) {
	    int v, no = 0;
	    for (int i = 0; i < text.size(); ++i) {
	        while (tree[no].link.find(text[i]) == tree[no].link.end()) {
	            if (no == 0) { tree[0].link[text[i]] = 0; break; }
	            no = tree[no].fail;
	        }
	        v = no = tree[no].link[text[i]];
	        // marcar os encontrados
	        while (v != -1 /* && !tree[v].marc */ ) { // p/ decisao
	            //tree[v].marc = true; // p/ decisao: nao continua a link
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
 
