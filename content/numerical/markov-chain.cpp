/**
 * Author: LeticiaFCS
 * Date: 2021-06-18
 * Description: Markov Chain
 * Row sums of the transition matrix need to be 1 and prob vector sum also needs to be 1.
 * Returns if the prob vector converges and the converged vector
 * Status: Working on URI Midnight Cowboy
 * Not well tested! Arbitrary limits, be careful
 */

template<typename D = double> 
auto MarkovChain(vector<vector<D>> trans, vector<D> prob, D eps = 1e-8, int it = 40000){
	int n = (int) trans.size();
	vector<D> last;
	bool converged = false;	
	while( !converged && it-- ){
		last.swap(prob);  prob = vector<D>(n);
		converged = true;
		for(int i = 0; i < n; i++) for(int j = 0; j < n; j++)
			prob[i] += last[j] * trans[j][i];			
		for(int i = 0; i < n && converged; i++)
			converged = abs(last[i] - prob[i]) < eps;
	}	
	return make_pair(converged, prob);
}
