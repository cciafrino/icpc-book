/**
 * Author: Paulo Miranda (adapted by LeticiaFCS)
 * Date: 
 * License: 
 * Source: Paulo Miranda
 * Description: RangeColor structure, supports point queries and range updates, 
 * if $C$ isn't int32\_t change $freq$ to map
 * Status: Tested on URI 2698
 * Time: $O(\lg(L)*Q)$
 * Status: stress-tested
 */
template<class T, class C> struct RangeColor { ///start-hash
	struct Node{
		T lo, hi; C color;
		bool operator<(const Node &n) const { return hi < n.hi; }
	};
	C minInf; set<Node> st; vector<T> freq;
	RangeColor(T first, T last, C maxColor, C iniColor = C(0)): minInf(first - T(1)), freq(maxColor + 1) {
		freq[iniColor] = last - first + T(1);
		st.insert({first, last, iniColor});
	} ///end-hash
	C query(T i) { //get color in position i
		return st.upper_bound({T(0), i - T(1), minInf})->color;
	}
	void upd(T a, T b, C x) { //set x in [a, b] ///start-hash
		auto p = st.upper_bound({T(0), a - T(1), minInf});
		assert(p != st.end());
		T lo = p->lo, hi = p->hi; C old = p->color;
		freq[old] -= (hi - lo + T(1)); p = st.erase(p);
		if (lo < a)
			freq[old] += (a-lo), st.insert({lo, a-T(1), old});
		if (b < hi)
			freq[old] += (hi-b), st.insert({b+T(1), hi, old});
		while ((p != st.end()) && (p->lo <= b)) {
			lo = p->lo, hi = p->hi; old = p->color;
			freq[old] -= (hi - lo + T(1));
			if (b < hi){
				freq[old] += (hi - b); st.erase(p);
				st.insert({b + T(1), hi, old});
				break;
			} else p = st.erase(p);
		}
		freq[x] += (b - a + T(1)); st.insert({a, b, x});
	} ///end-hash
	T countColor(C x){ return freq[x]; }
};
