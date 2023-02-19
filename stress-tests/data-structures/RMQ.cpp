#include "../utilities/template.h"

#include "../../content/data-structures/rmq.h"

int main() {
	srand(2);
	rep(N,0,100) {
		vi v(N); 
		rep(i,0,N) v[i] = i;
		random_shuffle(all(v));
		rmq_t<int> rmq(v);
		rep(i,0,N) rep(j,i+1,N+1) {
			int m = rmq.query(i,j);
			int n = 1 << 29;
			rep(k,i,j) n = min(n, v[k]);
			assert(n == m);
		}
	}
	cout<<"Tests passed!"<<endl;
}
