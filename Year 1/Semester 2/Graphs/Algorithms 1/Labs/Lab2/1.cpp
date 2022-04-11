#include <iostream>
#include <bits/stdc++.h>
using namespace std;
ifstream fin("graf.txt");
#define inf 1e5
const int sz=15;

void read(vector <int> v[sz], int& n, int& start_node){

    fin>>n>>start_node;
    int x,y;


    while(fin>>x>>y)
        v[x].push_back(y);



}
void bfs(int n, vector <int> v[sz], int start_node, int d[], int t[]){
    queue<int>q;
    q.push(start_node);

    d[start_node]=0;
    t[start_node]=-1;

    for (int i=1; i<=n; i++)
        if (i!=start_node)
            d[i]=inf;

    while(!q.empty()){

        int node=q.front();
        q.pop();

        for (auto el:v[node]){

            if (d[el]==inf){
                q.push(el);
                d[el]=d[node]+1;
                t[el]=node;
            }
        }

    }
    t[start_node]=-1;
}
void lant(int d[], int t[], int n){
    int Min=inf+1;
    int nod=0;
    for (int i=1; i<=n; i++){
        if (d[i]<Min && d[i]!=0){
            Min=d[i];
            nod=i;
        }
    }

    while(nod!=-1){
        cout<<nod<<" ";
        nod=t[nod];
    }

}
void lant1(int d[], int t[], int n){
    int Min=inf+1;
    int nod=0;
    for (int i=1; i<=n; i++){ 

        nod=i;
        if (d[i]==inf)
            cout<<"Nu exista!\n";
        else{ 
            cout<<"Lantul cu distanta " <<d[nod]<< " pana la nodul "<<i<<" este: ";
            while(nod!=-1){
                cout<<nod<<" ";
                nod=t[nod];
            }
            cout<<endl;
        }


    }

}
int main(){

    vector <int> v[sz];
    queue<int>q;

    int n, start_node;
    int drumuri[sz]={0},tati[sz]={0};

    read(v,n,start_node);
    bfs(n, v, start_node, drumuri, tati);
    lant1(drumuri,tati,n);

    return 0;


}
