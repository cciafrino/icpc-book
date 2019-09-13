/**
 * Author: Chris
 * Date: 2016-08-23
 * License: CC0
 * Source: me
 * Description: 
 */

const int SZ = 9;
int n=SZ;

bool isPossible(int mat[][SZ],int i,int j,int no){
    ///Row or col should not have no
    for(int x=0;x<n;x++){
        if(mat[x][j]==no||mat[i][x]==no){
            return false;
        }
    }
    /// Subgrid should not have no
    int sx = (i/3)*3;
    int sy = (j/3)*3;
    for(int x=sx;x<sx+3;x++){
        for(int y=sy;y<sy+3;y++){
            if(mat[x][y]==no){
                return false;
            }
        }
    }
    return true;
}
void printMat(int mat[][SZ]){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<mat[i][j]<<" ";
            if((j+1)%3==0){
                cout<<'\t';
            }
        }
         if((i+1)%3==0){
                cout<<endl;
        }
            cout<<endl;
    }
}
bool solveSudoku(int mat[][SZ],int i,int j){
    ///Base Case
    if(i==SZ){
        printMat(mat);
        return true;
    }
    ///Crossed the last  Cell in the row
    if(j==SZ) return solveSudoku(mat,i+1,0);
    ///Skip if filled cell
    if(mat[i][j]!=0){
        return solveSudoku(mat,i,j+1);
    }
    ///White Cell
    ///Try to place every possible no
    for(int no=1;no<=SZ;no++){
        if(isPossible(mat,i,j,no)){
            ///Place the no - assuming solution is possible with this
            mat[i][j] = no;
            bool isSolve=solveSudoku(mat,i,j+1);
            if(isSolve){
                return true;
            }
            ///loop will place the next no.
        }
    }
    ///Backtracking
    mat[i][j] = 0;
    return false;
}

int main(){

	int mat[SZ][SZ] =
        	{{5,3,0,0,7,0,0,0,0},
       	 	{6,0,0,1,SZ,5,0,0,0},
		{0,SZ,8,0,0,0,0,6,0},
		{8,0,0,0,6,0,0,0,3},
		{4,0,0,8,0,3,0,0,1},
		{7,0,0,0,2,0,0,0,6},
		{0,6,0,0,0,0,2,8,0},
		{0,0,0,4,1,SZ,0,0,5},
		{0,0,0,0,8,0,0,7,SZ}};
	printMat(mat);
	cout<<"Solution "<<endl;
	solveSudoku(mat,0,0);
return 0;
}
