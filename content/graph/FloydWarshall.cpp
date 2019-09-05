const int N = 555;
vector<vector<int>> adj;
int n;

void FloydWarshall(){
    for (int k = 0; k < n; ++k){
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j)
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
        }
    }
}