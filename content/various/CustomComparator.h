/**
 * Author: ?
 * Date: 2020
 * License:
 * Source: ?
 * Description: 
 * Usage: 
 * Status: works
 */
auto cmp = [](const kind_t& a, const kind_t& b) {
    return a.func() < b.func();
};
set<kind_t, decltype(cmp)> my_set(cmp);
map<kind_t, int, decltype(cmp)> my_map(cmp);
priority_queue<kind_t, vector<kind_t>, decltype(cmp)> my_pq(cmp);

