/**
 * Author: BenQ
 * Description: find least integer $p$ such that $r^p=x$(mod $m$)
 * Time: O(\sqrt{mod}) 
 */
template<typename T>
struct DiscreteLog {
	T mod, root, block;
	unordered_map<T,T> u;
	T cur = 1; /// start-hash
	DiscreteLog(T root, T mod) : mod(mod), root(root) {block = sqrt(mod)+1;}
	T query(T x) { 
		for (int i = 0; i < block; ++i) {
			if (u.count(x)) return ((i * block) % mod) + u[x];
			x = (x * cur) % mod;
		}
		return -1;
	}/// end-hash
	/// start-hash
	void init() { // gcd(m,r) = 1
		u.clear(); 
		T cur = 1;
        for (int i = 0; i < block; ++i) {
			if (!u.count(cur)) u[cur] = i;
			cur = (cur * root) % mod;
		}
		cur = 1/cur;
	} /// end-hash
};
