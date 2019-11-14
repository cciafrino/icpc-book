/**
 * Author: Arthur Nascimento
 * Description: Dynamic Segment 
 * Source: https://codeforces.com/submissions/arthur.nascimento
 */

template<typename T>
struct paretto {
    set<point> S;
    set<point> :: iterator it, aux;
    T INF, NINF;
    lint area;
    void add(point a,point b){
        if(a.second+1) area -= (lint) a.Y * (b.X - a.X);
    }
    void rem(point a,point b){
        if(a.second+1) area += (lint) a.Y * (b.X - a.X);
    }
    paretto(int n){
        INF = inf;
        NINF = -inf;
        area = 0;
        point a ({NINF,INF},-1);
        point b ({n+1,NINF},-1);
        S.insert(a);
        S.insert(b);
        add(a,b);
    }
    point query(T x){
        it = S.lower_bound(point({x,INF},-1));
        return *(--it);
    }
    void insert(T x,T y,int id){
    
        point lo = query(x);
        if(lo.Y <= y) return;
        point P ({x,y},id);
        S.insert(P);
        aux = it = S.find(P);
        it++;
        aux--;
        rem(*aux,*it);
        add(*aux,P);
        
        while(1){
            it = S.find(P); it++;
            if(it->Y < y) break;
            aux = it; aux++;
            rem(*it,*aux);
            S.erase(it);
        }   
        it = S.find(P); it++;
        add(P,*it);
    }
};