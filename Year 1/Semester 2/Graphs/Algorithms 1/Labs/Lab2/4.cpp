#include <bits/stdc++.h>

using namespace std;
ifstream fin("graf4.txt");


const int sz=15;

void read(vector <int> v[sz], int& n){

    fin>>n;

    int x,y;

    while(fin>>x>>y){ 
        v[x].push_back(y);
        v[y].push_back(x);
    }
}

void dfs_visit(vector <int> v[sz], int nod, int viz[]){ 
    viz[nod]=1;
    cout<<nod<<" ";
    for (auto el:v[nod])
        if (!viz[el])
            dfs_visit(v,el,viz);
}
void dfs(vector <int> v[sz], int n){
    int viz[sz]; 
    for (int i=1; i<=n; i++){ 
        viz[i]=0;
    }

    for (int i=1; i<=n; i++)
        if (!viz[i]){ 
            
            dfs_visit(v,i,viz);
            cout<<'\n';
        }
}

int main(){ 
    vector<int>v[sz];

    int n;

    read(v,n);
    dfs(v,n);
    
    return 0;

}
