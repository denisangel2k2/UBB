//decod prufer
#include <bits/stdc++.h>

using namespace std;

vector<int>prufer;
vector<pair<int,int>>muchii;

int findMin(vector<int>prufer,int j){
    vector<int>frecv(100001,0);
    int Max=-2;
    for (int i=j; i<prufer.size(); i++)
    {
        Max=max(prufer[i],Max);
        frecv[prufer[i]]=1;
    }

    for (int i=0; i<prufer.size()+1; i++){
        if (frecv[i]==0)
            return i;
    }

    return -2;
}

void decodarePrufer(char* argv[]){
    ofstream fout(argv[2]);

    int n=prufer.size();
    for (int j=0; j<n; j++){
        int nod=findMin(prufer,j);
        //
        if (nod!=-2){
            muchii.push_back(make_pair(nod,prufer[j]));
            prufer.push_back(nod);
        }

    }
    vector<int>tati(n+1,-1);
    for (auto el:muchii)
        tati[el.first]=el.second;

    fout<<tati.size()<<'\n';
    for (auto el:tati)
        fout<<el<<" ";

}
int main(int argc, char* argv[]){
    ifstream fin(argv[1]);
    

    int n;
    fin>>n;
    int x;
    for (int i=0; i<n; i++){
        fin>>x;
        prufer.push_back(x);
    }
    decodarePrufer(argv);
    return 0;
}
