/**
 * Author: stevenhalim (adapted)
 * Description: NQueens
 */

int ans;
bitset<30> rw, ld, rd; //2*MAX_N -1
bitset<30> iniqueens; //2*MAX_N -1
vector<int> col;
void init(int n){
	ans=0;
    rw.reset();
    ld.reset();
    rd.reset();
    col.assign(n,-1);
}
void init(int n, vector<pair<int,int>> initial_queens){
    //it does NOT check if initial queens are at valid positions
    init(n);
    iniqueens.reset();
    for(pair<int,int> pos: initial_queens){
        int r=pos.first, c= pos.second;
        rw[r] = ld[r-c+n-1] = rd[r+c]=true;
        col[c]=r;
        iniqueens[c] = true;
    }
}
void backtracking(int c, int n){
    if(c==n){
    	ans++;
        for(int r:col) cout<<r+1<<" ";
        cout<<"\n";
        return;
    }
    else if(iniqueens[c]){
        backtracking(c+1,n);
    }
    else for(int r=0;r<n;r++){
        if(!rw[r] && !ld[r-c+n-1] && !rd[r+c]){ 
        // if(board[r][c]!=blocked && !rw[r] && !ld[r-c+n-1] && !rd[r+c]){ // if there are blocked possitions
            rw[r] = ld[r-c+n-1] = rd[r+c]=true;
            col[c]=r;
            backtracking(c+1,n);
            col[c]=-1;
            rw[r] = ld[r-c+n-1] = rd[r+c]=false;
        }
    }
}
