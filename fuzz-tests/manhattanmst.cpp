#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

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
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

struct UF {
	vector<int> e;
	UF(int n) : e(n, -1) {}
	bool same_set(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool unite(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return 0;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return 1;
	}
};

typedef Point<int> P;
pair<vector<array<int, 3>>, int> manhattanMST(vector<P> ps) {
    vector<int> id(ps.size());
    iota(id.begin(), id.end(), 0);
    vector<array<int, 3>> edges;
    for(int s = 0; s < 2; ++s) {
        for(int t = 0; t < 2; ++t) {
            sort(id.begin(), id.end(), [&](int i, int j) {
                 return (ps[i]-ps[j]).x < (ps[j]-ps[i]).y;});
            map<int, int> sweep;
            for (int i: id) {
                for (auto it = sweep.lower_bound(-ps[i].y);
                            it != sweep.end(); sweep.erase(it++)) {
                    int j = it->second;
                    auto d = ps[j] - ps[i];
                    if (d.y < d.x) break;
                    edges.push_back({abs(d.y) + abs(d.x), i, j});
                }
                sweep[-ps[i].y] = i;
            }
            for (auto &p: ps) p = P(p.y, p.x);
        }
        for (auto &p: ps) p = P(-p.x, p.y);
    }
    sort(edges.begin(), edges.end());
    UF uf(ps.size());
    int cost = 0;
    for (auto e: edges) if (uf.unite(e[1], e[2])) cost += e[0];
    return {edges, cost};
}

typedef Point<int> P;
double rectilinear_mst_n(vector<P> ps) {
  struct edge { int src, dst; double weight; };
  vector<edge> edges;

  auto dist = [&](int i, int j) {
    return abs((ps[i]-ps[j]).x) + abs((ps[i]-ps[j]).y);
  };
  for (int i = 0; i < ps.size(); ++i)
    for (int j = i+1; j < ps.size(); ++j)
      edges.push_back({i, j, dist(i,j)});
  double cost = 0;
  sort(all(edges), [](edge a, edge b) { return a.weight < b.weight; });
  UF uf(ps.size());
  for (auto e: edges)
    if (uf.unite(e.src, e.dst))
      cost += e.weight;
  return cost;
}

signed main() {
	clock_t t1, t2;
    for (int t=0; t<100; t++) {
        int num_pts = 1000;
        vector<P> pts;
        for (int i = 0; i < num_pts; ++i) {
            double x = rand() % 300;
            double y = rand() % 300;

            pts.push_back(P(x,y));
        }
        t1 = clock();
        auto ret = manhattanMST(pts);
    	t1 = clock() - t1;
    	t2 = clock();
        assert(ret.second == rectilinear_mst_n(pts));
        t2 = clock() - t2;
    }
    cout << (double)t1/CLOCKS_PER_SEC << ' ' << (double)t2/CLOCKS_PER_SEC << endl;

} 