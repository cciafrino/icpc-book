/**
 * Author: Andrew He
 * Date: 2020
 * License: 
 * Source: cp-book
 * Description: A set (not multiset!) with support for finding the n'th
 * element, and finding the index of an element.
 * Time: O(\log N)
 */
#include<bits/extc++.h>

template <typename K, typename V, typename Comp = std::less<K>>
using ordered_map = __gnu_pbds::tree<
	K, V, Comp,
	__gnu_pbds::rb_tree_tag,
	__gnu_pbds::tree_order_statistics_node_update
>;

template <typename K, typename Comp = std::less<K>>
using ordered_set = ordered_map<K, __gnu_pbds::null_type, Comp>;

void example() {
	ordered_set<int> t, t2; t.insert(8);
	auto it = t.insert(10).first;
	assert(it == t.lower_bound(9));
	assert(t.order_of_key(10) == 1); // num strictly smaller
	assert(t.order_of_key(11) == 2);
	assert(*t.find_by_order(0) == 8);
	t.join(t2); // assuming T < T2 or T > T2, merge t2 into t
}
