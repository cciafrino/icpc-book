/**
 * Author: Chris
 * Date: 2018
 * License: CC0
 * Source: me
 * Status: Tested on UVA 989
 * Description: 
 */
int N,m; // N = n*n, m = n; where n equal number of rows or columns
array<array<int, 10>, 10> grid;
struct SudokuSolver {    
    bool UsedInRow(int row,int num){
        for(int col = 0; col < N; ++col) 
            if(grid[row][col] == num) return true;
        return false;
    }
    bool UsedInCol(int col,int num){
        for(int row = 0; row < N; ++row) 
            if(grid[row][col] == num) return true;
        return false;
    }
    bool UsedInBox(int row_0,int col_0,int num){
        for(int row = 0; row < m; ++row) 
            for(int col = 0; col < m; ++col)
                if(grid[row+row_0][col+col_0] == num) return true;
        return false;
    }
    bool isSafe(int row,int col,int num){
        return !UsedInRow(row,num) && !UsedInCol(col,num) && !UsedInBox(row-row%m,col-col%m,num);
    }
    bool find(int &row,int &col){
        for(row = 0; row < N; ++row) 
            for(col = 0; col < N; ++col)
                if(grid[row][col] == 0) return true;
        return false;
    }
    bool Solve(){
        int row, col;
        if(!find(row,col)) return true;
        for(int num = 1; num <= N; ++num){
            if(isSafe(row,col,num)){
                grid[row][col] = num;
                if(Solve()) return true;
                grid[row][col] = 0;
            }
        }
        return false;
    }
};

