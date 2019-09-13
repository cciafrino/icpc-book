/**
 * Author: Chris
 * Date: 2016-08-23
 * License: CC0
 * Source: me
 * Description: Maximum rectangle in histogram
 */
 
lint histogram(lint vet[], int n) {
	stack<lint> s;
	lint ans = 0, tp, cur;
	int i = 0;
	while(i < n || !s.empty()) {
		if (i < n && (s.empty() || vet[s.top()] <= vet[i])) s.push(i++);
		else {
			tp = s.top();
			s.pop();
			cur = vet[tp] * (s.empty() ? i : i - s.top() - 1);
			if (ans < cur) ans = cur;
		}
	}
	return ans;
}

