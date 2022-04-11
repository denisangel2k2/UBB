#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;
#define INF 1e4+1
const int sz=1e4+2;
#define cout fout
struct triplet{
    int x,y,cost;
};

void read(vector<triplet>& m, int& nV, int& nE, char* input){
    ifstream fin(input);
    fin>>nV>>nE;
    int x,y,z;
    for (int i=1; i<=nE; i++){
        fin>>x>>y>>z;
        m.push_back(triplet{x,y,z});
    }
}
void init(int d[], int nV){
    for (int i=0; i<nV; i++)
        d[i]=INF;
}
bool bellman_ford(const vector<triplet>& m, int d[], int nV){

    init(d,nV);
    int nod_nou=1e4+1;
    d[nod_nou]=0;
    for (int i=1; i<=nV; i++)
        for (auto muchie:m)
            if (d[muchie.y]>d[muchie.x]+muchie.cost)
                d[muchie.y]=d[muchie.x]+muchie.cost;

    for (auto muchie:m)
        if (d[muchie.y]>d[muchie.x]+muchie.cost)
            return false;

    return true;    
        

}

void dijkstra(const vector<vector<pair<int,int>>> v, int d[], int start, int nV){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
    init(d,nV);
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
vector<vector<pair<int,int>>> copyList(const vector<triplet>& m, int nV){
    vector<vector<pair<int,int>>>v(nV, vector<pair<int,int>>(0));
    for (auto el:m)
        v[el.x].push_back(make_pair(el.y,el.cost));
    
    return v;
}

bool johnson(vector<triplet>& m, int nV, int nE, char* output){
    int dist[sz];
    init(dist,nV);
    int nod_nou=1e4+1;
    ofstream fout(output);
    vector<triplet>muchii_noi;

    for (auto el:m)
        muchii_noi.push_back(el);

    for (int nod=0; nod<nV; nod++)
        muchii_noi.push_back(triplet{nod_nou,nod,0}); // am adaugat noul nod la graf


    int d[sz];
    bool areThereNegativeCircuits=bellman_ford(muchii_noi,d,nV);

    if (areThereNegativeCircuits==false)
        return false;
    
    vector<triplet>muchii;
   
    for (auto el:m) //schimbam ponderile
        muchii.push_back(triplet{el.x,el.y,d[el.x]+el.cost-d[el.y]});
    
    for (auto el:muchii)
        cout<<el.x<<" "<<el.y<<" "<<el.cost<<'\n';

  
    vector<vector<pair<int,int>>> lista=copyList(muchii,nV);

    for (int start=0; start<nV; start++){


        dijkstra(lista,dist,start,nV);

        for (int i=0; i<nV; i++)
            if (dist[i]==INF)
                cout<<"INF ";
            else
                cout<<dist[i]-d[start]+d[i]<<" ";
        fout<<'\n';
    }
    return true;
    
}
int main(int argc, char* argv[]){
     

    int nV,nE;
    vector<triplet>muchii;
    ofstream fout(argv[2]);
    read(muchii,nV,nE,argv[1]);

    if (!johnson(muchii,nV,nE,argv[2]))
        fout<<-1;
    

    
    return 0;
}