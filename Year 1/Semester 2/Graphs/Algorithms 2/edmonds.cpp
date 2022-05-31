#include <bits/stdc++.h>


using namespace std;

const int sz=1005;
int graf[sz][sz];
int rgraf[sz][sz];

int V,E;

bool bfs(int start, int t, int tati[]){

    bool viz[sz]={0};
    queue<int>q;
    q.push(start);
    viz[start]=true;

    tati[start]=-1;
    while(!q.empty()){
        int nod=q.front();
        q.pop();
        for (int i=0; i<V; i++){
            if (!viz[i] && rgraf[nod][i]>0){
                if (i==t){
                    tati[i]=nod;
                    return true;
                }
                q.push(i);
                tati[i]=nod;
                viz[i]=true;
            }
        }

    }
    return false;
}

int edmondskarp(int start,int t){
    
    for (int i=0; i<V; i++)
        for (int j=0; j<V; j++)
            rgraf[i][j]=graf[i][j];

    int tati[sz];
    int fluxMax=0;
    while(bfs(start,t,tati)){
        int flux=INT_MAX;

        for (int nod=t; nod!=start; nod=tati[nod]){
            int parinte=tati[nod];
            flux=min(flux,rgraf[parinte][nod]);
        }

        for (int nod=t; nod!=start; nod=tati[nod]){
            int parinte=tati[nod];
            rgraf[parinte][nod]-=flux;
            rgraf[nod][parinte]+=flux;
        }
        fluxMax+=flux;
    }

    return fluxMax;
}

int main(int argc, char** argv){
    

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    int x,y,c;
    fin>>V>>E;
    for (int i=0; i<E; i++){
        fin>>x>>y>>c;
        graf[x][y]=c;
    }
    int s=0;
    int t=V-1;
    fout<<edmondskarp(s, t);

    return 0;
}



