#include <bits/stdc++.h>
#include <fstream>

using namespace std;
int V,E;
vector<pair<int,int>>lista[5000];
void Prim(int start,ofstream& fout){

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
            q.push(make_pair(0,start));

            int cost_final=0;
            int tati[V]={0};
            int adaugat[V]={0};
            for (int i=0; i<V; i++)
                adaugat[i]=0;
            vector<pair<int,int>>muchii_arbore;
            
            while(!q.empty()){
                int nod=q.top().second;
                int cost=q.top().first;
                q.pop();
                if (!adaugat[nod]){
                    adaugat[nod]=1;
                    if (nod!=start) muchii_arbore.push_back(make_pair(nod,tati[nod]));
                    cost_final+=cost;
                }
                for (auto vecin:lista[nod]){
                    if (!adaugat[vecin.first]){
                        q.push(make_pair(vecin.second,vecin.first));
                        tati[vecin.first]=nod;
                    }
                }
            }
            
            fout<<cost_final<<'\n'<<muchii_arbore.size()<<'\n';
            for (auto el:muchii_arbore)
                fout<<el.first<<" "<<el.second<<'\n';
}

int main(int argc, char* argv[]){

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    
    fin>>V>>E;
    int x,y,c;
    
    int start;

    for (int i=0; i<E; i++){
        fin>>x>>y>>c;
        start=x;
        lista[x].push_back(make_pair(y,c));
        lista[y].push_back(make_pair(x,c));
        }
    


    Prim(start,fout);

    return 0;
}

