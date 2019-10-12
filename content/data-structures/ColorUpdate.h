/**
 * Author: tfg50
 * Description: 
 */
template<typename T>
struct Color {
	struct Range {
		T v;
		int lx, rx;
		Range(int lx = 0) { this->lx = lx; }
		Range(int lx, int rx, T v) {
			this->lx = lx; this->rx = rx;
			this->v = v;
		}
		bool operator<(const Range &o) { return lx < o.lx; }
	};
	set<Range> ranges;
	vector<Range> update(int lx, int rx, T v) {
		vector<Range> ret;
		if (lx >= rx) return ret;
		auto it = ranges.lower_bound(lx);
		if (it != ranges.begin()) {
			it--;
			if (it->rx > lx) {
				auto cur = *it;
				ranges.erase(it);
				ranges.insert(Range(cur.lx, lx, cur.v));
				ranges.insert(Range(lx, cur.rx, cur.v));
			}
		}
		it = ranges.lower_bound(rx);
		if (it != ranges.begin()) {
			it--;
			if (it->rx > rx) {
				auto cur = *it;
				ranges.erase(it);
				ranges.insert(Range(cur.lx, rx, cur.v));
				ranges.insert(Range(rx, cur.rx, cur.v));
			}
		}
		for (it = ranges.lower_bound(lx); it != ranges.end() && it->lx < rx; ++it) 
			ret.push_back(*it);
		ranges.erase(ranges.lower_bound(lx), ranges.lower_bound(rx));
		ranges.insert(Range(lx, rx, v));
		return ret;
	}
};