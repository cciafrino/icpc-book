/**
 * Description: Examples of Segment Tree with Lazy update
 */
//	Range sum query - { 'n', 0 }
//	Range add update - { 'a', x } 
//	Range set update - { 's', x }
// if (x.type != id_z.type) // (D)
// if (lazy[v].type != id_z.type) // (G)
namespace range_sum_range_add_range_set{
	using T = int64_t;
	struct node{
		char type;
		T v;
	};
	auto F = [](const T &a, const T &b){
		return a + b;
	};
	auto US = [](const node &lazy, const T &num, T len = 0){
		T v = lazy.v * len;
		if(lazy.type == 'a') v += num;
		return v;
	};
	auto UY = [](const node &par, const node &ch){
		if(par.type == 's') return par;
		T v = ch.v + par.v;
		if(ch.type == 'n') return node{ 'a', v }; 
		return node{ ch.type, v };
	};
}
// BE CAREFULL!! The first term will be a0 + d NOT a0
//	Range sum query - { 'n', 0, 0 }
//	Range add arithmetic progression update - { 'a', a0, d } 
//	Range set arithmetic progression update - { 's', a0, d } 
// T query(int v, int l, int r, int a, int b, NZ x) { //(A)
// if (a < l) x.a += (l-a) * x.r, a = l; // (B)
// if (x.type != id_z.type) // (D)
// if (lazy[v].type != id_z.type) // (G)
// tree[vR] = s(lazy[v], tree[vR], r - md, md - l); // (I)
// lazy[vR] = y(lazy[v], lazy[vR], md - l); // (K)
namespace range_sum_range_addAP_range_setAP{
	using T = int64_t;
	struct node{
		char type;
		T a, r;
	};
	const auto F = [](const T& a, const T& b) {
		return a + b;
	};
	const auto US = [](const node& lazy, const T& num, T len, T left = 0) {
		T v = ( (len + left + 1) * (len + left)/2 - (left + 1) * left/2 ) * lazy.r + len * lazy.a;
		if(lazy.type == 'a') v += num;
		return v;
	};
	const auto UY = [](const node& par, const node& ch, T left = 0) {
		T a = par.a + par.r * left;
		T r = par.r;
		if(par.type == 's') return node{ 's', a, r };
		a += ch.a;
		r += ch.r;
		if(ch.type == 'n') return node{ 'a', a, r };
		return node{ ch.type, a, r };
	};
}
