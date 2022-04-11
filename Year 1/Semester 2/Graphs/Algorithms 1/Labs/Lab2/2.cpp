#include <iostream>
#include <bits/stdc++.h>


using namespace std;
ifstream fin("graf2.txt");

const int sz=15;

void read(vector <int> v[sz], int& n){

    fin>>n;

    int x,y;

    while(fin>>x>>y)
        v[x].push_back(y);
}

void dfs(vector<int>v[sz], int nod, int viz[]){ 
    viz[nod]=1;
    for (auto el:v[nod])
        if (!viz[el])
            dfs(v,el,viz);
}
void remake(int viz[] ,int n){ 
    for (int i=1; i<=n; i++)
        viz[i]=0;
}
void tranzitiva(int tranz[sz][sz], int n, vector<int>v[sz]){ 
    int viz[sz]={0};
    for (int i=1; i<=n; i++){ 
        remake(viz,n);
        dfs(v,i,viz);
        for (int j=1; j<=n; j++)
            tranz[i][j]=viz[j];
    }
}
int main(){ 
    
    int n;
    int tranz[sz][sz]={0};
    
    vector <int>v[sz];

    read(v,n);
    tranzitiva(tranz,n,v);

    for (int i=1; i<=n; i++){ 
        for (int j=1; j<=n; j++)
            cout<<tranz[i][j]<<" ";
        cout<<'\n';
    }




    return 0;

}
