/**
 * Author: Paulo Miranda (adapted by LeticiaFCS)
 * Date: 
 * License: 
 * Source: Paulo Miranda
 * Description: RangeColor structure, supports point queries and range updates
 * if $C$ isn't int32_t change $freq$ to map<C, int64_t>
 * Status: Tested on URI 2698
 * Time: $O(\lg(L)*Q)$
 * Status: not well tested
 */

template<class T = int64_t, class C = int32_t> struct RangeColor{

	struct Node{
		T l, r;
		C color;
		bool operator<(const Node &n) const{return r < n.r;}
	};
	
	C minInf;
	set<Node> st;
	vector<int64_t> freq;
	
	RangeColor(T first, T last, C maxColor, C iniColor = 0, C minusInf = -1): minInf(minusInf), freq(maxColor + 1) {
		freq[iniColor] = last - first + 1LL;
		st.insert(Node({first, last, iniColor}));
	}
	//get color in position i
	C query(T i){
		auto p = st.upper_bound(Node({0, i - 1LL, minInf}));
		return p->color;
	}
	//set newColor in [a, b]
	void upd(T a, T b, C newColor){
		auto p = st.upper_bound(Node({0, a - 1LL, minInf}));
		assert(p != st.end());
		T l = p->l, r = p->r;
		C old = p->color;
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
	T countColor(C x){
		return freq[x];
	}
};
