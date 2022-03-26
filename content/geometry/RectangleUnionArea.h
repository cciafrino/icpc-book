/**
 * Author: Felipe Chen
 * Date: 
 * License: CC0
 * Source: 
 * Description: Sweep line algorithm that calculates area of union of rectangles in the form $[x1,x2) \times [y1,y2)$
 * Usage: Create vector with both $x$ coordinates and $y$ coordinates of each rectangle.//vector<pair<int,int>,pair<int,int>> rectangles;// rectangles.push_back({{x1, x2}, {y1, y2}});// lint result = area(rectangles);
 * Status: tested
 */
struct seg_node{
	int val, cnt, lz;
	seg_node(int n = INT_MAX, int c = 0): val(n), cnt(c), lz(0) {}
	void push(seg_node& l, seg_node& r){
		if(lz){
			l.add(lz);
			r.add(lz);
			lz = 0;
		}
	}
	void merge(const seg_node& l, const seg_node& r){
		if(l.val < r.val) val = l.val, cnt = l.cnt;
		else if(l.val > r.val) val = r.val, cnt = r.cnt;
		else val = l.val, cnt = l.cnt + r.cnt;
	}
	void add(int n){
		val += n;
		lz += n;
	}
	int get_sum(){ return (val ? 0 : cnt); }
};
// x1 y1 x2 y2
lint solve(const vector<array<int, 4>>&v){
	vector<int>ys;
	for(auto& [a, b, c, d] : v){
		ys.push_back(b);
		ys.push_back(d);
	}
	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());
	vector<array<int, 4>>e;
	for(auto [a, b, c, d] : v){
		b = int(lower_bound(ys.begin(), ys.end(), b) - ys.begin());
		d = int(lower_bound(ys.begin(), ys.end(), d) - ys.begin());
		e.push_back({a, b, d, 1});
		e.push_back({c, b, d, -1});
	}
	sort(e.begin(), e.end());
	int m = (int)ys.size();
	segtree_range<seg_node>seg(m-1);
	for(int i=0;i<m-1;i++) seg.at(i) = seg_node(0, ys[i+1] - ys[i]);
	seg.build();
	int last = INT_MIN, total = ys[m-1] - ys[0];
	lint ans = 0;
	for(auto [x, y1, y2, c] : e){
		ans += (lint)(total - seg.query(0, m-1).get_sum()) * (x - last);
		last = x;
		seg.update(y1, y2, &seg_node::add, c);
	}
	return ans;
}
