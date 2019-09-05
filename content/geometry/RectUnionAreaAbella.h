/**
 * Author: Felipe Abella
 * Date: 
 * License: CC0
 * Source: 
 * Description: Line sweep algorithm that find the area of union of rectangles. 
 */

struct rectangle_union_area_t { ///start-hash
  lint area = 0LL;
  set<pii> active;
  lint get_area_contribution(set<pii>::iterator it) {
    int width = it->first, height = it->second;
    if (it != active.begin()) {
      --it;
      width -= it->first;
      ++it;
    }
    {
      ++it;
      if (it != active.end()) {
        height -= it->second;
      }
      --it;
    }
    return (lint)width * height;
  }///end-hash

  void add(int x, int y) {///start-hash
    if (!is_covered(x, y)) {
      set<pii>::iterator it;
      while (it = get_covered_by(x, y), it != active.end()) {
        area -= get_area_contribution(it);
        active.erase(it);
      }
      area += get_area_contribution(active.insert(make_pair(x, y)).first);
    }
  }///end-hash

  set<pii>::iterator get_covered_by(int x, int y) {///start-hash
    auto it = active.upper_bound(make_pair(x, INT_MAX));
    if (it != active.begin()) {
      --it;
      if (it->second <= y)
        return it;
    }
    return active.end();
  }///end-hash

  bool is_covered(int x, int y) {///start-hash
    auto it = active.lower_bound(make_pair(x, INT_MIN));
    return it != active.end() && it->second >= y;
  }

  lint get_area() { return area; }
};///end-hash

