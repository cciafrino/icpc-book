/**
 * Author: LeticiaFCS
 * Date: 2019-09-12
 * Description: Markov Chain 
 * Status: Working on URI Midnight Cowboy
 */

//1-indexed
int adj[N][N]; //adj matrix
int out[N]; // out degree of the state
double trans[N][N], prob[N];

void create_prob(int n, int s=1){
	for(int i=1;i<=n;i++) prob[i]=0;
	prob[s]=1;
}
void create_chain(int n){
	for(int i=1;i<=n;i++){
		if(out[i])
			for(int j=1;j<=n;j++){
				if(adj[i][j])
					trans[i][j]=((double)adj[i][j])/out[i];
				else
					trans[i][j]=0;
			}
		else
			for(int j=1;j<=n;j++) trans[i][j]=1.0/n;
	}
}

double aux[N];
int aplica(int n){
	for(int i=1;i<=n;i++) aux[i]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			aux[i]+=prob[j]*trans[j][i];
	int dif=0;
	for(int i=1;i<=n;i++){
		dif+=abs(cmp_double(prob[i]*prob[i],aux[i]*aux[i],1e-15));
		prob[i]=aux[i];
	}
	return dif;
}


void solve(int n){
	while(aplica(n));
}

