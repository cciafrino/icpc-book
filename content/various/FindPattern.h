/**
 * Author: Chris
 * Date: 2016-08-23
 * License: CC0
 * Source: me
 * Description: 
 */
 
bool test(vector<int> &v, int init, int size, int lim){
	for(int i = init; i < lim; ++i)
		if(v[init + ((i-init)%size)] != v[i])
			return false;
	return true;
}

void identifyPattern(vector<int> &v, int lim){
	for(int init = 0; init < lim; ++init){
		for(int size = 1; size < 500; ++size){
			if(test(v, init, size, lim)){
				cout << init << " " << size << endl;				
				break;
			}
		}
	}
}
