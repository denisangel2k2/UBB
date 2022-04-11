#include <vector>
#include <iostream>
#include <fstream>
#include <queue>




using namespace std;

#define INF 1e4

struct triplet{
    int x,y,cost;
};

void dijkstra1(vector<pair<int,int>> v[], int nV, int start, int d[]){
    priority_queue< pair<int,int>, vector<pair<int,int> >, greater<pair<int,int>> >q;
    q.push(make_pair(0,start));
    d[start]=0;

    while(!q.empty()){
        int nod=q.top().second;
        q.pop();

        for (auto el:v[nod]){
            int nod_vecin=el.first;
            int cost_toVecin=el.second;
            if (d[nod_vecin]>d[nod]+cost_toVecin){
                d[nod_vecin]=d[nod]+cost_toVecin;
                q.push(make_pair(d[nod_vecin],nod_vecin));
            }
        }
    }
}

bool bellman_ford(vector<triplet>& m, int d[], int nV, int start){
    d[start]=0;
    for (int i=1; i<=nV; i++){
        for (auto el:m)
            if (d[el.y]>d[el.x]+el.cost) //relax
                d[el.y]=d[el.x]+el.cost;
    }
    for (auto el:m)
        if (d[el.y]>d[el.x]+el.cost) //relax
            return false;
    return true;
}
void init(int d[], int n){
    for (int i=0; i<n; i++)
        d[i]=INF;
}
int main(int argc, char* argv[]){

    const int sz=1e4+1;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]); 

    vector< pair<int,int> >lista[10000];
    vector < triplet >muchii;

    int nV,nE,start;

    fin>>nV>>nE>>start;
    int x,y,z;

    cout<<nV<<" "<<nE<<" "<<start;

    for (int i=1; i<=nE; i++){
        fin>>x>>y>>z;
        lista[x].push_back(make_pair(y,z));
        triplet t={x,y,z};
        muchii.push_back(t);
    }
    int d[sz];
    init(d,nV);

    /*
    bellman_ford(muchii,d,nV,start);

    for (int i=0; i<nV; i++)
        if (d[i]==INF)
            fout<<"INF ";
        else
            fout<<d[i]<<" ";

    
    */
    init(d,nV);
    dijkstra1(lista,nV,start,d);

    for (int i=0; i<nV; i++)
        if (d[i]==INF)
            fout<<"INF ";
        else
            fout<<d[i]<<" ";

    fin.close();
    fout.close();
    return 0;
}