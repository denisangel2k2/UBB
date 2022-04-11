#include <bits/stdc++.h>
#include <iostream>
using namespace std;

ifstream fin("graf3.txt");
const int sz=15;
#define inf 1e5
void read(vector<int>v[sz], int &n, int &start_node){ 
    fin>>n>>start_node;
    int x,y;
    while(fin>>x>>y)
        v[x].push_back(y);
}
void bfs(vector<int>v[sz], int start_node, int n){ 
    deque<int>q;
    int drum[sz];

    for (int i=1; i<=n; i++)
        drum[i]=inf;

    drum[start_node]=0;
    q.push_back(start_node);

    vector<int>vizitati;

    while(!q.empty()){ 
        int nod=q.front();
        q.pop_front();
        vizitati.push_back(nod);
        for (auto el:v[nod])
            if (drum[el]==inf)
            { 
                drum[el]=drum[nod]+1;
                q.push_back(el);
                
            }
    }

    for (int i=0; i<vizitati.size(); i++){ 
            cout<<vizitati[i]<<" distanta fata de varful "<<start_node<<" este "<<drum[vizitati[i]];
        cout<<'\n';
    }

    

}
int main(){ 
    int n;
    vector<int>v[sz];
    int start;
    read(v,n,start);
    bfs(v,start, n);


    return 0;

}
