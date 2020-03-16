#include <bits/stdc++.h>
using namespace std;
#define TAM 100000
int r1, r2;
void buscaBinaria(int soma, int arr[]){ 
    int pos1, pos2;
    bool sit = false;
    int fim = sizeof(arr) + 1;
    int ini = 0;
    for(int i = 0; i < fim; i++){
        while(ini <= fim){
            int m = ini + (fim - ini)/2;
            if(abs(arr[i] + arr[m]) == abs(soma)){
                if(i != m){
                    pos1 = i;
                    pos2 = m;
                    sit = true;
                    break;
                }    
            }
            if(abs(arr[i] + arr[m]) < abs(soma)){
                ini = m + 1;
            }else if (abs(arr[i] + arr[m]) > abs(soma)){
                fim = m - 1;
            }
        }
        if(sit == true){
            if(arr[pos1] >= arr[pos2]){
                r1 = arr[pos2];
                r2 = arr[pos1];
            } else if(arr[pos1] < arr[pos2]){
                r1 = arr[pos1];
                r2 = arr[pos2];
            }
            return;
        }

        fim = sizeof(arr) + 1;
        ini = 0;
    }
    return;    
}
int main(){
    int num;
    int casas[TAM];
    int soma;
    cin >> num;
    for(int i = 0; i < num; i++ ){
        cin >> casas[i];
    }
    cin >> soma;
    buscaBinaria(soma, casas);
    printf("%d %d\n", r1, r2);

    return 0;
}
