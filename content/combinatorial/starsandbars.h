// Stars and Stripes inclusion-exclusion
	ll ans = 0;
	for (int mask = 0; mask < (1<<n); ++mask) {
		ll tot = s;
		int parity = 1;
		for (int j = 0; j < n; ++j) {
			if (mask & (1<<j)) {
				tot -= fs[j]+1;
				parity *= -1;
			}
		}
		if (tot < 0) continue;
		ans += parity * choose(tot + n-1, n-1);
	}