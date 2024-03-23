/**
 * Author: Krzysztof Potępa
 * Description: Faster/better hash maps, taken from teapot
 */
#include<bits/extc++.h> /** keep-include */
const size_t HXOR = std::mt19937_64(time(0))();
template<class T> struct SafeHash {
	size_t operator()(const T& x) const {
		return std::hash<T>()(x ^ T(HXOR));
	}
};
template <typename K, typename V, typename Hash = SafeHash<K>>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;
template <typename K, typename Hash = SafeHash<K>>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>; }
