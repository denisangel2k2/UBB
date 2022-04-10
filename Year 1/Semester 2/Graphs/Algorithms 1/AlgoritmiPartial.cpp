#include <bits/stdc++.h>

using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt");

struct triplet{
    int in,out,cost;

    triplet(int _in, int _out, int _cost) : in{_in}, out{_out}, cost{_cost}{}
};

int viz[50];
vector<int>lista[50];
vector< pair<int,int> >listac[50];
vector<triplet>muchii;
int dist[50];
int n,m;



void dfs(int nod){
    fout<<nod<<" ";
    viz[nod]=1;
    for (auto el:lista[nod])
        if (!viz[el])
            dfs(el);

}
void bfs(int nod){
    queue<int>q;
    q.push(nod);
    viz[nod]=1;
    while(!q.empty()){

        int nd=q.front();

        fout<<nd<<" ";
        q.pop();
        for (auto el : lista[nd])
            if (!viz[el]){
                q.push(el);
                viz[el]=1;
                }
    }
}
bool bellman_ford(int nod, int dist[], const vector<triplet>& muchii, int n, int m){

    for (int i=1; i<=n; i++)
        dist[i]=1e5;
    dist[nod]=0;


    for (int i=1; i<=n; i++){
        for (int j=0; j<m; j++)
            if (dist[muchii[j].out]>dist[muchii[j].in]+muchii[j].cost)
                dist[muchii[j].out]=dist[muchii[j].in]+muchii[j].cost;
    }

    for (int j=0; j<m; j++)
            if (dist[muchii[j].out]>dist[muchii[j].in]+muchii[j].cost)
                return false;
    return true;
}
void dijkstra(int nod, int dist[], vector<pair<int,int>>listac[]){

    for (int i=1; i<=n; i++)
        dist[i]=1e5;
    dist[nod]=0;

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
    q.push(make_pair(0,nod));

    while(!q.empty()){
        int nd=q.top().second;
        int cst=q.top().first;
        q.pop();

        for (auto vecin : listac[nd]){
            int nod_vecin=vecin.first;
            int cost_toVecin=vecin.second;

            if (dist[nod_vecin]>dist[nd]+cost_toVecin){
                dist[nod_vecin]=dist[nd]+cost_toVecin;
                q.push(make_pair(dist[nod_vecin],nod_vecin));
            }
        }
    }
}
bool johnson(int nod,vector<pair<int,int>>listac[],const vector<triplet>& muchii, int dist[], int n, int m){
    int newNode=49; // in general iau numarul sa fie mai mare decat numarul maxim de noduri posibile
    int dist2[50];

    for (int i=1; i<=n; i++)
        dist2[i]=1e5;

    dist2[newNode]=0;
    vector<triplet>new_muchii;

    for (auto el:muchii)
        new_muchii.push_back(el);

    for (int node=1; node<=n; node++)
        new_muchii.push_back(triplet{newNode,node,0});

    int d[50];
    bool negativeCircuits=bellman_ford(newNode,d,new_muchii,n,m);





    if (!negativeCircuits)
        return false;
    else{
        vector<triplet>muchii_ponderi;
        for (auto el:muchii)
            muchii_ponderi.push_back(triplet{el.in,el.out,d[el.in]+el.cost-d[el.out]});

        vector<pair<int,int>>lista_noua[50];

        for (auto el:muchii_ponderi) // construiesc lista de adiacenta
            lista_noua[el.in].push_back(make_pair(el.out,el.cost));


        /*
        for (int start=1; start<=n; start++){
            dijkstra(start,dist2,lista_noua);

            //distanta de la start la nodul i este : dist[i]=dist2[i]-d[start]+d[i], d-distanta cu bellman ford, dist2 - distanta cu dijkstra
            for (int i=1; i<=n; i++)
                dist[i]=dist2[i]-d[start]+d[i];
        }
        */
        dijkstra(nod,dist2,lista_noua);
        for (int i=1; i<=n; i++)
            dist[i]=dist2[i]-d[nod]+d[i];

        return true;

    }

}
int main(){
    fin>>n>>m;
    int x,y,cost;
    for (int i=1; i<=m; i++){
        fin>>x>>y>>cost;
        muchii.push_back(triplet{x,y,cost});

        listac[x].push_back(make_pair(y,cost));
        listac[y].push_back(make_pair(x,cost));

        lista[x].push_back(y);
        lista[y].push_back(x);
    }

    return 0;
}
