/**
 * Author: LeticiaFCS
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
 
//	Range sum query - { 'n', 0, 0 }
//	Range add arithmetic progression update - { 'a', a0, d } 
//	Range set arithmetic progression update - { 's', a0, d } 
// T query(int v, int l, int r, int a, int b, NZ x) { //(A)
// if (a < l) x.a += (l-a) * x.d, a = l; // (B)
// if (x.type != id_z.type) // (D)
// if (lazy[v].type != id_z.type) // (G)
// tree[vR] = s(lazy[v], tree[vR], r - md, md - l); // (I)
// lazy[vR] = y(lazy[v], lazy[vR], md - l); // (K)
namespace range_sum_range_addAP_range_setAP{
	using T = int64_t;
	struct node{
		char type;	
		T a, d;
	};
	const auto F = [](const T& a, const T& b) {
		return a + b;
	};
	const auto US = [](const node& lazy, const T& num, T len, T addRhs = 0) {
		T v = len * (2LL * (lazy.a + addRhs * lazy.d) + (len - 1LL) * lazy.d) / 2LL ;
		if(lazy.type == 'a') v += num;
		return v;
	};
	const auto UY = [](const node& par, const node& ch, T addRhs = 0) {
		if(par.type == 's') return par;
		T a = ch.a + par.a + addRhs * par.d;
		T d = ch.d + par.d;
		if(ch.type == 'n') return node{ 'a', a, d }; 
		return node{ ch.type, a, d };
	};
}
 
