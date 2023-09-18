/**
 * Author: xyz111
 * Date: 2015-09-01
 * License: CC0
 * Description: Geometry 2D Library
 * Status: somewhat tested
 */
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};
using P = Point<double>;

template<class P>
double lineDist(const P& a, const P& b, const P& p) {
	return (double)(b-a).cross(p-a)/(b-a).dist();
}
double segDist(P& s, P& e, P& p) {
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}
template<class P> vector<P> segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
		 oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return {(a * ob - b * oa) / (ob - oa)};
	set<P> s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return {s.begin(), s.end()};
}
template<class P>
bool segmentIntersectionQ(P s1, P e1, P s2, P e2) {
	if (e1 == s1) {
		if (e2 == s2) return e1 == e2;
		swap(s1,s2); swap(e1,e2);
	}
	P v1 = e1-s1, v2 = e2-s2, d = s2-s1;
	auto a = v1.cross(v2), a1 = d.cross(v1), a2 = d.cross(v2);
	if (a == 0) { // parallel
		auto b1 = s1.dot(v1), c1 = e1.dot(v1),
			 b2 = s2.dot(v1), c2 = e2.dot(v1);
		return !a1 && max(b1,min(b2,c2)) <= min(c1,max(b2,c2));
	}
	if (a < 0) { a = -a; a1 = -a1; a2 = -a2; }
	return (0 <= a1 && a1 <= a && 0 <= a2 && a2 <= a);
}
template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}
template<class P>
P lineProj(P a, P b, P p, bool refl=false) {
	P v = b - a;
	return p - v.perp()*(1+refl)*v.cross(p-a)/v.dist2();
}
template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
	auto a = (e-s).cross(p-s);
	double l = (e-s).dist()*eps;
	return (a > l) - (a < -l);
}
template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
P linearTransformation(const P& p0, const P& p1,
	const P& q0, const P& q1, const P& r) {
	P dp = p1-p0, dq = q1-q0, num(dp.cross(dq), dp.dot(dq));
	return q0 + P((r-p0).cross(num), (r-p0).dot(num))/dp.dist2();
}
template <class P>
bool sameDir(P s, P t) {
	return s.cross(t) == 0 && s.dot(t) > 0;
}
// checks 180 <= s..t < 360?
template <class P>
bool isReflex(P s, P t) {
	auto c = s.cross(t);
	return c ? (c < 0) : (s.dot(t) < 0);
}
// operator < (s,t) for angles in [base,base+2pi)
template <class P>
bool angleCmp(P base, P s, P t) {
	int r = isReflex(base, s) - isReflex(base, t);
	return r ? (r < 0) : (0 < s.cross(t));
}
// is x in [s,t] taken ccw? 1/0/-1 for in/border/out
template <class P>
int angleBetween(P s, P t, P x) {
	if (sameDir(x, s) || sameDir(x, t)) return 0;
	return angleCmp(s, x, t) ? 1 : -1;
}
int half(P p) { return p.y != 0 ? sgn(p.y) : -sgn(p.x); }
bool angle_cmp(P a, P b) { int A = half(a), B = half(b);
	return A == B ? a.cross(b) > 0 : A < B; }
bool circleInter(P a,P b,double r1,double r2,pair<P, P>* out) {
	if (a == b) { assert(r1 != r2); return false; }
	P vec = b - a;
	double d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
		   p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return false;
	P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	*out = {mid + per, mid - per};
	return true;
}
template<class P>
vector<pair<P, P>> tangents(P c1, double r1, P c2, double r2) {
	P d = c2 - c1;
	double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
	if (d2 == 0 || h2 < 0)  return {};
	vector<pair<P, P>> out;
	for (double sign : {-1, 1}) {
		P v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
		out.push_back({c1 + v * r1, c2 + v * r2});
	}
	if (h2 == 0) out.pop_back();
	return out;
}
double ccRadius(const P& A, const P& B, const P& C) {
	return (B-A).dist()*(C-B).dist()*(A-C).dist()/
		abs((B-A).cross(C-A))/2;
}
P ccCenter(const P& A, const P& B, const P& C) {
	P b = C-A, c = B-A;
	return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}
pair<P, double> mec(vector<P> ps) {
	shuffle(ps.begin(),ps.end(), mt19937(time(0)));
	P o = ps[0];
	double r = 0, EPS = 1 + 1e-8;
	for(int i = 0; i < ps.size(); ++i) 
		if ((o - ps[i]).dist() > r * EPS) {
			o = ps[i], r = 0;
			for(int j = 0; j < i; ++j) if ((o - ps[j]).dist() > r * EPS) {
				o = (ps[i] + ps[j]) / 2;
				r = (o - ps[i]).dist();
				for(int k = 0; k < j; ++k) 
					if ((o - ps[k]).dist() > r * EPS) {
						o = ccCenter(ps[i], ps[j], ps[k]);
						r = (o - ps[i]).dist();
					}
			}
		}
	return {o, r};
}
template<class P>
vector<P> circleLine(P c, double r, P a, P b) {
	double h2 = r*r - a.cross(b,c)*a.cross(b,c)/(b-a).dist2();
	if (h2 < 0) return {};
	P p = lineProj(a, b, c), h = (b-a).unit() * sqrt(h2);
	if (h2 == 0) return {p};
	return {p - h, p + h};
}
template<class P>
double circleCircleArea(P c, double cr, P d, double dr) {
	if (cr < dr) swap(c, d), swap(cr, dr);
	auto A = [&](double r, double h) {
		return r*r*acos(h/r)-h*sqrt(r*r-h*h);
	};
	auto l = (c - d).dist(), a = (l*l + cr*cr - dr*dr)/(2*l);
	if (l - cr - dr >= 0) return 0; // far away
	if (l - cr + dr <= 0) return M_PI*dr*dr;
	if (l - cr >= 0) return A(cr, a) + A(dr, l-a);
	else return A(cr, a) + M_PI*dr*dr - A(dr, a-l);
}
#define arg(p, q) atan2(p.cross(q), p.dot(q))
double circlePoly(P c, double r, vector<P> ps) {
	auto tri = [&](P p, P q) {
		auto r2 = r * r / 2;
		P d = q - p;
		auto a = d.dot(p)/d.dist2(), b = (p.dist2()-r*r)/d.dist2();
		auto det = a * a - b;
		if (det <= 0) return arg(p, q) * r2;
		auto s = max(0., -a-sqrt(det)), t = min(1., -a+sqrt(det));
		if (t < 0 || 1 <= s) return arg(p, q) * r2;
		P u = p + d * s, v = p + d * t;
		return arg(p,u) * r2 + u.cross(v)/2 + arg(v,q) * r2;
	};
	auto sum = 0.0;
	for (int i = 0; i < ps.size(); ++i)
		sum += tri(ps[i] - c, ps[(i + 1) % ps.size()] - c);
	return sum;
}
template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
	int cnt = 0, n = p.size();
	for(int i = 0; i < n; ++i) {
		P q = p[(i + 1) % n];
		if (onSegment(p[i], q, a)) return !strict; // change to
				// -1 if u need to detect points in the boundary
		//or: if (segDist(p[i], q, a) <= eps) return !strict;
		cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
	}
	return cnt;
}
template<class T>
T polygonArea(vector<Point<T>> &v) {
	T a = v.back().cross(v[0]);
	for(int i = 0; i < v.size()-1; ++i) 
		a += v[i].cross(v[i+1]);
	return abs(a)/2.0;
}

Point<T> polygonCentroid(vector<Point<T>> &v) { // not tested
	Point<T> cent(0,0); T area = 0;
	for(int i = 0; i < v.size(); ++i) {
		int j = (i+1) % (v.size()); T a = cross(v[i], v[j]);
		cent += a * (v[i] + v[j]);
		area += a;
	}
	return cent/area/(T)3;
}
P polygonCenter(const vector<P>& v) {
	P res(0, 0); double A = 0;
	for (int i = 0, j = v.size() - 1; i < v.size(); j = ++i) {
		res = res + (v[i] + v[j]) * v[j].cross(v[i]);
		A += v[j].cross(v[i]);
	}
	return res / A / 3;
}
vector<P> polygonCut(const vector<P>& poly, P s, P e) {
	vector<P> res;
	for(int i = 0; i < poly.size(); ++i) {
		P cur = poly[i], prev = i ? poly[i-1] : poly.back();
		bool side = s.cross(e, cur) < 0;
		if (side != (s.cross(e, prev) < 0))
			res.push_back(lineInter(s, e, cur, prev).second);
		if (side) res.push_back(cur);
	}
	return res;
}
vector<P> convexHull(vector<P> pts) {
	if (pts.size() <= 1) return pts;
	sort(pts.begin(), pts.end());
	vector<P> h(pts.size()+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end()))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}
array<P, 2> hullDiameter(vector<P> S) {
	int n = S.size(), j = n < 2 ? 0 : 1;
	pair<lint, array<P, 2>> res({0, {S[0], S[0]}});
	for(int i = 0; i < j; ++i)
		for (;; j = (j + 1) % n) {
			res = max(res, {(S[i] - S[j]).dist2(), {S[i], S[j]}});
			if ((S[(j + 1) % n] - S[j]).cross(S[i + 1] - S[i]) >= 0)
				break;
		}
	return res.second;
}
bool inHull(const vector<P> &l, P p, bool strict = true) {
	int a = 1, b = l.size() - 1, r = !strict;
	if (l.size() < 3) return r && onSegment(l[0], l.back(), p);
	if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
	if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
		return false;
	while (abs(a - b) > 1) {
		int c = (a + b) / 2;
		(sideOf(l[0], l[c], p) > 0 ? b : a) = c;
	}
	return sgn(l[a].cross(l[b], p)) < r;
}
vector<P> minkowski_sum(vector<P> A, vector<P> B) {
	if (int(A.size()) > int(B.size())) swap(A, B);
	if (A.empty()) return {};
	if (int(A.size()) == 1) {
		for (auto& b : B) b = b + A.front();
		return B;
	}
	rotate(A.begin(), min_element(A.begin(), A.end()), A.end());
	rotate(B.begin(), min_element(B.begin(), B.end()), B.end());
	A.push_back(A[0]); A.push_back(A[1]);
	B.push_back(B[0]); B.push_back(B[1]);
	const int N = int(A.size()), M = int(B.size());
	vector<P> ans; ans.reserve(N+M);
	for (int i = 0, j = 0; i+2 < N || j+2 < M;) {
		ans.push_back(A[i] + B[j]);
		auto sgn = (A[i+1] - A[i]).cross(B[j+1] - B[j]);
		i += (sgn >= 0); j += (sgn <= 0);
	}
	return ans;
}
double rat(P a, P b) { return sgn(b.x) ? a.x/b.x : a.y/b.y; }
double polyUnion(vector<vector<P>>& poly) {
	double ret = 0;
	for(int i = 0; i < poly.size(); ++i) 
		for(int v = 0; v < poly[i].size(); ++v) {
			P A = poly[i][v], B = poly[i][(v + 1) % poly[i].size()];
			vector<pair<double, int>> segs = {{0, 0}, {1, 0}};
			for(int j = 0; j < poly.size(); ++j) if (i != j) {
				for(int u = 0; u < poly[j]; ++u) {
					P C = poly[j][u], D = poly[j][(u + 1) % poly[j].size()];
					int sc = sideOf(A, B, C), sd = sideOf(A, B, D);
					if (sc != sd) {
						double sa = C.cross(D, A), sb = C.cross(D, B);
						if (min(sc, sd) < 0)
							segs.emplace_back(sa / (sa - sb), sgn(sc - sd));
					} else if (!sc && !sd && j<i && sgn((B-A).dot(D-C))>0){
						segs.emplace_back(rat(C - A, B - A), 1);
						segs.emplace_back(rat(D - A, B - A), -1);
					}
				}
		}
		sort(segs.begin(), segs.end());
		for(auto& s : segs) s.first = min(max(s.first, 0.0), 1.0);
		double sum = 0;
		int cnt = segs[0].second;
		for(int j = 1; j < segs.size(); ++j) {
			if (!cnt) sum += segs[j].first - segs[j - 1].first;
			cnt += segs[j].second;
		}
		ret += A.cross(B) * sum;
	}
	return ret / 2;
}
typedef array<P, 2> Line;
#define cmp(i,j) sgn(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
int extrVertex(vector<P>& poly, P dir) { ///start-hash
	int n = poly.size(), left = 0, right = n;
	if (extr(0)) return 0;
	while (left + 1 < right) {
		int m = (left + right) / 2;
		if (extr(m)) return m;
		int ls = cmp(left + 1, left), ms = cmp(m + 1, m);
		(ls < ms || (ls == ms && ls == cmp(left, m)) ? right : left) = m;
	}
	return left;
}///end-hash

#define cmpL(i) sgn(line[0].cross(poly[i], line[1]))
array<int, 2> lineHull(Line line, vector<P>& poly) { ///start-hash
	int endA = extrVertex(poly, (line[0] - line[1]).perp());
	int endB = extrVertex(poly, (line[1] - line[0]).perp());
	if (cmpL(endA) < 0 || cmpL(endB) > 0)
		return {-1, -1};
	array<int, 2> res;
	for(int i = 0; i < 2; ++i) {
		int left = endB, right = endA, n = poly.size();
		while ((left + 1) % n != right) {
			int m = ((left + right + (left < right ? 0 : n)) / 2) % n;
			(cmpL(m) == cmpL(endB) ? left : right) = m;
		}
		res[i] = (left + !cmpL(right)) % n;
		swap(endA, endB);
	}
	if (res[0] == res[1]) return {res[0], -1};
	if (!cmpL(res[0]) && !cmpL(res[1]))
		switch ((res[0] - res[1] + sz(poly) + 1) % poly.size()) {
			case 0: return {res[0], res[0]};
			case 2: return {res[1], res[1]};
		}
	return res;
} ///end-hash
#define eps 1e-8
typedef Point<double> P;

struct Line {
	P P1, P2;
	// Right hand side of the ray P1 -> P2
	explicit Line(P a = P(), P b = P()) : P1(a), P2(b) {};
	P intpo(Line y) {
		pair<int, P> r = lineInter(P1, P2, y.P1, y.P2);
		assert(r.first == 1);
		return r.second;
	}
	P dir() { return P2 - P1; }
	bool contains(P x) {
		return (P2 - P1).cross(x - P1) < eps;
	}
	bool out(P x) { return !contains(x); }
}; 

template<class T>
bool mycmp(Point<T> a, Point<T> b) {
	// return atan2(a.y, a.x) < atan2(b.y, b.x);
	if (a.x * b.x < 0) return a.x < 0;
	if (abs(a.x) < eps) {
		if (abs(b.x) < eps) return a.y > 0 && b.y < 0;
		if (b.x < 0) return a.y > 0;
		if (b.x > 0) return true;
	}
	if (abs(b.x) < eps) {
		if (a.x < 0) return b.y < 0;
		if (a.x > 0) return false;
	}
	return a.cross(b) > 0;
}

bool cmp(Line a, Line b) { return mycmp(a.dir(), b.dir()); }

double Intersection_Area(vector <Line> b) {
	sort(b.begin(), b.end(), cmp);
	int n = b.size();
	int q = 1, h = 0, i;
	vector<Line> c(b.size() + 10);
	for (i = 0; i < n; i++) {
		while (q < h && b[i].out(c[h].intpo(c[h - 1]))) h--;
		while (q < h && b[i].out(c[q].intpo(c[q + 1]))) q++;
		c[++h] = b[i];
		if (q < h && abs(c[h].dir().cross(c[h - 1].dir())) < eps) {
			if (c[h].dir().dot(c[h - 1].dir()) > 0) {
				h--;
				if (b[i].out(c[h].P1))	c[h] = b[i];
			}else {
				// The area is either 0 or infinite.
				// If you have a bounding box, then the area is definitely 0. 
				return 0;
			}
		}
	}
	while (q < h-1 && c[q].out(c[h].intpo(c[h - 1]))) h--;
	while (q < h-1 && c[h].out(c[q].intpo(c[q + 1]))) q++;
	// Intersection is empty. This is sometimes different from the case when
	// the intersection area is 0. 
	if (h - q <= 1) return 0;
	c[h + 1] = c[q];
	vector<P> s;
	for (i = q; i <= h; i++) s.push_back(c[i].intpo(c[i + 1]));
	s.push_back(s[0]);
	double ans = 0;
	for (i = 0; i < (int) s.size()-1; i++) ans += s[i].cross(s[i + 1]);
	return ans / 2;
}
pair<P, P> closest(vector<P> v) {
	assert(v.size() > 1);
	set<P> S;
	sort(v.begin(), v.end(), [](P a, P b) { return a.y < b.y; });
	pair<int64_t, pair<P, P>> ret{LLONG_MAX, {P(), P()}};
	int j = 0;
	for(P &p : v) {
		P d{1 + (int64_t)sqrt(ret.first), 0};
		while (v[j].y <= p.y - d.x) S.erase(v[j++]);
		auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
		for (; lo != hi; ++lo)
			ret = min(ret, {(*lo - p).dist2(), {*lo, p}});
		S.insert(p);
	}
	return ret.second;
}
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

