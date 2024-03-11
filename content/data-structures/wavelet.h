/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: Yosupo
 * Description: Segment tree on values instead of indices.
 * Time: $O(\log(n))$
 */
struct wavelet_t { ///start-hash
	struct BitVector { // space: 32N bits
		vector<int> _rank = {0};
		BitVector(vector<char> v = vector<char>()) {
			_rank.reserve(v.size() + 1);
			for (int d : v) _rank.push_back(_rank.back() + d);
		}
		int rank(bool f, int k) { return f ? _rank[k] : (k - _rank[k]); }
		int rank(bool f, int l, int r) { return rank(f, r) - rank(f, l); }
	}; ///end-hash
	/*
	   struct BitVector {  // space: 1.5N bits
	   vector<ull> v;
	   vector<int> _rank;
	   BitVector(vector<char> _v = vector<char>()) {
	   int n = int(_v.size());
	   v = vector<ull>((n + 63) / 64);
	   _rank = vector<int>(v.size() + 1);
	   for (int i = 0; i < n; i++) {
	   if (_v[i]) {
	   v[i / 64] |= 1ULL << (i % 64);
	   _rank[i / 64 + 1]++;
	   }
	   }
	   for (int i = 0; i < int(v.size()); i++) {
	   _rank[i+1] += _rank[i];
	   }
	   }
	   int rank(int k) {
	   int a = _rank[k / 64];
	   if (k % 64) a += __builtin_popcountll(v[k / 64] << (64 - k % 64));
	   return a;
	   }
	   int rank(bool f, int k) { return f ? rank(k) : k - rank(k); }
	   int rank(bool f, int l, int r) { return rank(f, r) - rank(f, l); }
	   };
	   */
	int n, lg = 1;///start-hash
	vector<int> mid;
	vector<BitVector> data;
	wavelet_t(vector<int> v = vector<int>()) : n(int(v.size())) {
		int ma = 0;
		for (int x : v) ma = max(ma, x);
		while ((1 << lg) <= ma) lg++;
		mid = vector<int>(lg);
		data = vector<BitVector>(lg);
		for (int lv = lg - 1; lv >= 0; lv--) {
			vector<char> buf;
			vector<vector<int>> nx(2);
			for (int d : v) {
				bool f = (d & (1 << lv)) > 0;
				buf.push_back(f);
				nx[f].push_back(d);
			}
			mid[lv] = int(nx[0].size());
			data[lv] = BitVector(buf);
			v.clear();
			v.insert(v.end(), nx[0].begin(), nx[0].end());
			v.insert(v.end(), nx[1].begin(), nx[1].end());
		}
	}///end-hash
	pair<int, int> succ(bool f, int a, int b, int lv) {
		int na = data[lv].rank(f, a) + (f ? mid[lv] : 0);
		int nb = data[lv].rank(f, b) + (f ? mid[lv] : 0);
		return {na, nb};
	}
	// count i, s.t. (a <= i < b) && (v[i] < u)
	int rank(int a, int b, int u) {///start-hash
		if ((1 << lg) <= u) return b - a;
		int ans = 0;
		for (int lv = lg - 1; lv >= 0; lv--) {
			bool f = (u & (1 << lv)) > 0;
			if (f) ans += data[lv].rank(false, a, b);
			tie(a, b) = succ(f, a, b, lv);
		}
		return ans;
	}///end-hash
	// k-th(0-indexed!) number in v[a..b]
	int select(int a, int b, int k) {///start-hash
		int u = 0;
		for (int lv = lg - 1; lv >= 0; lv--) {
			int le = data[lv].rank(false, a, b);
			bool f = (le <= k);
			if (f) {
				u += (1 << lv);
				k -= le;
			}
			tie(a, b) = succ(f, a, b, lv);
		}
		return u;
	}///end-hash
	// k-th(0-indexed!) largest number in v[a..b]
	int large_select(int a, int b, int k) { 
		return select(a, b, b - a - k - 1);
	}
	// count i s.t. (a <= i < b) && (x <= v[i] < y)
	int count(int a, int b, int x, int y) {
		return rank(a, b, y) - rank(a, b, x);
	}
	// max v[i] s.t. (a <= i < b) && (v[i] < x)
	int pre_count(int a, int b, int x) {
		int cnt = rank(a, b, x);
		return cnt == 0 ? -1 : select(a, b, cnt - 1);
	}
	// min v[i] s.t. (a <= i < b) && (x <= v[i])
	int nxt_count(int a, int b, int x) {
		int cnt = rank(a, b, x);
		return cnt == b - a ? -1 : select(a, b, cnt);
	}
};

struct CompressWavelet {///start-hash
	wavelet_t wt;
	vector<int> v, vidx;
	int zip(int x) {
		return int(lower_bound(vidx.begin(), vidx.end(), x) - vidx.begin());
	}
	CompressWavelet(vector<int> _v = vector<int>()) : v(_v), vidx(v) {
		sort(vidx.begin(), vidx.end());
		vidx.erase(unique(vidx.begin(), vidx.end()), vidx.end());
		for (auto& d : v) d = zip(d);
		wt = Wavelet(v);
	}
	int rank(int a, int b, int u) { return wt.rank(a, b, zip(u)); }
	int select(int a, int b, int k) { return vidx[wt.select(a, b, k)]; }
	int largest(int a, int b, int k) { return wt.large_select(a, b, k); }
	int count(int a, int b, int mi, int ma) { return wt.count(a, b, mi, ma); }
	int find_max(int a, int b, int x) { return wt.pre_count(a, b, x); }
	int find_min(int a, int b, int x) { return wt.nxt_count(a, b, x); }
};///end-hash
