/**
 * Author: Paulo Miranda (adapted by LeticiaFCS)
 * Date: 
 * License: 
 * Source: Paulo Miranda
 * Description: RangeColor structure, supports point queries and range updates
 * if $T$ is int32_t change $freq$ to a vector, set $maxColor$ value and resize $freq$
 * Status: Tested on URI 2698
 * Time: $O(\lg(L)*Q)$
 * Status: not well tested
 */

template<class T> struct RangeColor{

	struct Node{
		lint l, r;
		T color;
		bool operator<(const Node &n) const{return r < n.r;}
	};
	
	T minInf;
	set<Node> st;
	map<T, lint> freq;
	//vector<lint> freq;
	
	RangeColor(lint first, lint last, T iniColor = {}, T minusInf = -1 /*, T maxColor = {}*/): minInf(minusInf){
		//freq.resize(maxColor + 1); 
		freq[iniColor] = last - first + 1LL;
		st.insert(Node({first, last, iniColor}));
	}
	//get color in position i
	T query(lint i){
		auto p = st.upper_bound(Node({0, i - 1LL, minInf}));
		return p->color;
	}
	//set newColor in [a, b]
	void upd(lint a, lint b, T newColor){
		auto p = st.upper_bound(Node({0, a - 1LL, minInf}));
		assert(p != st.end());
		lint l = p->l, r = p->r;
		T old = p->color;
		freq[old] -= (r - l + 1LL);
		p = st.erase(p);
		if (l < a){
			freq[old] += (a - l);
			st.insert(Node({l, a - 1LL, old}));
		}
		if (b < r){
			freq[old] += (r - b);
			st.insert(Node({b + 1LL, r, old}));
		}
		while ((p != st.end()) and (p->l <= b)){
			l = p->l, r = p->r;
			old = p->color;
			freq[old] -= (r - l + 1LL);
			if (b < r){
				freq[old] += (r - b);
				st.erase(p);
				st.insert(Node({b + 1LL, r, old}));
				break;
			}else{
				p = st.erase(p);
			}
		}
		freq[newColor] += (b - a + 1LL);
		st.insert(Node({a, b, newColor}));
	}
	lint countColor(T x){
		return freq[x];
	}
};
