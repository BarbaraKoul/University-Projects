#include <iostream>
#include<stdio.h>
#include <vector>

using namespace std;

class UnionFind{
    public:
        UnionFind(int n){
            parent.resize(n+1);
            rank.resize(n+1,0);
            for(int i=0; i<=n; i++){
                parent[i]=i;
            }
        }
        int find(int x){
            if(parent[x]!=x){
                parent[x]=find(parent[x]);
            }
            return parent[x];
        }
        void UnionSets(int x, int y){
            int rootX=find(x);
            int rootY=find(y);
            if(rootX==rootY) return;
            if(rank[rootX]<rank[rootY]){
                parent[rootX]=rootY;
            }
            else if(rank[rootX]>rank[rootY]){
                parent[rootY]=rootX;
            }
            else{
                parent[rootY]=rootX;
                rank[rootX]++;
            }
        }
        bool SameSet(int x, int y){
            return find(x)==find(y);
        }
    private:
        vector<int> parent, rank;

};

int main(){
    int N, M, K, village1, village2, counter;
    scanf("%d %d %d", &N, &M, &K);
    UnionFind villages(N);
    counter=N;
    for (int i=0; i<M; i++){
        scanf("%d %d", &village1, &village2);
        if(!villages.SameSet(village1, village2)){
            villages.UnionSets(village1,village2);
            counter--;
        }
        if(counter==1){
            break;
        }
        
    }
    if(counter==1 ||(counter-K)<=1){
        printf("%d\n", 1);
    }
    else{
        int num=counter-K;
        printf("%d\n", num);
    }
    return 0;
}