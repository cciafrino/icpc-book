/**
 * Author: LeticiaFCS
 * Description: BFS on grid
 * Time: O(n*m)
 */

int numdir = 4; //8
int diri[] = {0,1,0,-1}; //{0,1,1,1,0,-1,-1,-1}
int dirj[] = {1,0,-1,0}; //{1,1,0,-1,-1,-1,0,1}

int grid[MAXN][MAXM];
int dist[MAXN][MAXM]; //initially -1

int n,m;

bool valid(int i, int j){
	if(i<0 || i>=n) return 0;
	if(j<0 || j>=m) return 0;
	if(dist[i][j]!=-1 || grid[i][j]==0) return 0;
	return 1;
}

void bfs(int x, int y){
	queue<pair<int,int>> q;
	q.push({x,y});
	dist[x][y]=0;
	
	while(!q.empty()){
		pair<int,int> f=q.front();
		q.pop();
		for(int d=0;d<numdir;d++){
			int pi = f.st + diri[d];
			int pj = f.nd + dirj[d];
			if(valid(pi,pj)){
					dist[pi][pj]=1+dist[f.st][f.nd];
					q.push({pi,pj});
			}			
		}
	}
}

