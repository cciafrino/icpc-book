/**
 * Author: Paulo Miranda (adapted by LeticiaFCS)
 * Date: 
 * License: 
 * Source: Paulo Miranda
 * Description: RangeColor structure, supports point queries and range updates
 * if $C$ isn't int32\_t change $freq$ to map
 * Status: Tested on URI 2698
 * Time: $O(\lg(L)*Q)$
 * Status: stress-tested
 */

template<class T = int64_t, class C = int32_t> struct RangeColor{

	struct Node{
		T l, r;
		C color;
		bool operator < (const Node &n) const{ return r < n.r; }
	};
	
	C minInf;
	set<Node> st;
	vector<T> freq;
	
	RangeColor(T first, T last, C maxColor, C iniColor = C(0)): minInf(first - T(1)), freq(maxColor + 1) {
		freq[iniColor] = last - first + T(1);
		st.insert({first, last, iniColor});
	}
	//get color in position i
	C query(T i){
		auto p = st.upper_bound({T(0), i - T(1), minInf});
		return p->color;
	}
	//set newColor in [a, b]
	void upd(T a, T b, C newColor){
		auto p = st.upper_bound({T(0), a - T(1), minInf});
		assert(p != st.end());
		T l = p->l, r = p->r;
		C old = p->color;
		freq[old] -= (r - l + T(1));
		p = st.erase(p);
		if (l < a){
			freq[old] += (a - l);
			st.insert({l, a - T(1), old});
		}
		if (b < r){
			freq[old] += (r - b);
			st.insert({b + T(1), r, old});
		}
		while ((p != st.end()) && (p->l <= b)){
			l = p->l, r = p->r;
			old = p->color;
			freq[old] -= (r - l + T(1));
			if (b < r){
				freq[old] += (r - b);
				st.erase(p);
				st.insert({b + T(1), r, old});
				break;
			} else	p = st.erase(p);
		}
		freq[newColor] += (b - a + T(1));
		st.insert({a, b, newColor});
	}
	T countColor(C x){ return freq[x]; }
};
