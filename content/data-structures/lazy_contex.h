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
