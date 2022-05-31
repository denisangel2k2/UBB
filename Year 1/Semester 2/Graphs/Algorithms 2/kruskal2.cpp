#include <bits/stdc++.h>

using namespace std;

struct triplet{
    int first, second, third;
};

int n,m;
const int sz=500;
vector<int>L(sz);
vector<pair<int,int>>tree;
vector<triplet>edges;
int cost;

void unite(int i,int j){

    for (int k=0; k<L.size(); k++){
        if (L[k]==j)
            L[k]=i;
    }
}

void kruskal(ofstream& fout){

    for (int i=0; i<n; i++)
        L[i]=i;

    for (auto edge : edges){
        if (L[edge.first]!=L[edge.second]){
            cout<<"\t\t"<<edge.first<<" "<<edge.second<<endl;
            unite(L[edge.first], L[edge.second]);
            cost+=edge.third;
            tree.push_back(make_pair(edge.first,edge.second));
        }
    }

    fout<<cost<<endl<<tree.size()<<endl;
    for (auto edge : tree)
        fout<<edge.first<<" "<<edge.second<<endl;

}

int main(int argc, char** argv){

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);


    int x,y,c;
    fin>>n>>m;
    for (int i=1; i<=m; i++){
        fin>>x>>y>>c;
        edges.push_back(triplet{x,y,c});
    }
    sort(edges.begin(),edges.end(),[](triplet t1, triplet t2){if (t1.third<t2.third) return true; return false;});
    for (auto edge : edges)
        cout<<edge.first<<" "<<edge.second<<" "<<edge.third<<endl;
    kruskal(fout);
    return 0;
}
