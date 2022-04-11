#include <bits/stdc++.h>

using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt");


const int sz=50;
stack<int>s;
vector<int>graf[sz];
vector<int>graf_transpus[sz];
vector<vector<int>>componente;
int viz[sz];
int n,m;

void read(){
    fin>>n>>m;
    int x,y;
    for (int i=1; i<=m; i++)
    {
        fin>>x>>y;
        graf[x].push_back(y);
        graf_transpus[y].push_back(x);
    }
}

void dfs(int nod){

    viz[nod]=1;
    for (auto el : graf[nod])
        if (viz[el]==0)
            dfs(el);

    s.push(nod);
}

void dfs_transvers(int nod, vector<int>& c){
    viz[nod]=0;
    c.push_back(nod);
    for (auto el : graf_transpus[nod])
        if (viz[el])
            dfs_transvers(el,c);
}

void kosaraju(){

    for (int nod=1; nod<=n; nod++)
        if (!viz[nod])
            dfs(nod);

    while (!s.empty()){
        int nod=s.top();
        s.pop();
        if (viz[nod]){
            vector<int>comp;
            dfs_transvers(nod,comp);
            componente.push_back(comp);
        }
    }




    cout<<componente.size()<<endl;
    for (auto el:componente)
    {
        for (auto el1:el)
            cout<<el1<<" ";
        cout<<endl;
    }

}


int main()
{

    read();
    kosaraju();

    return 0;
}
