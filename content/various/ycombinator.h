/**
 * Author: Andrew He
 * Date: 2020
 * License: 
 * Source: https://stackoverflow.com/a/40873657/2014771
 * Description: Efficient recursive lambda without overhead of std::function.
 * Usage: std::y_combinator([&] (auto self, int v) -> void {})(0, 0);
 		auto check = std::y_combinator([&] (auto self, int v) -> void {});
 * Status: Not well tested.
 */

namespace std {
template<class F>
class y_combinator_result {
	F fun_;
public:
	template<class T>
	explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
	template<class ...Args>
	decltype(auto) operator()(Args &&...args) {
		return fun_(std::ref(*this), std::forward<Args>(args)...);
	}
};
template<class F>
decltype(auto) y_combinator(F &&fun) {
	return y_combinator_result<std::decay_t<F>>(std::forward<F>(fun));
}}