//cod pruf

#include <bits/stdc++.h>

using namespace std;


vector<int>tati(100001);
vector<int>viz(100001);
vector<int>prufer;
int findMin(int n){
    vector<int>frecv(100001,0);
    int Max=-2;
    for (int i=0; i<n; i++)
    {
        if (tati[i]>=0)
            frecv[tati[i]]=1;
    }
    //cout<<frecv[0]<<endl;
    for (int i=0; i<n; i++){
        if (frecv[i]==0 && tati[i]>=0){
            //tati[i]=-2;
            return i;
        }
    }
    

    return -2;
}

void Prufer(int n){
    int frunzaMin=0;
    while(frunzaMin!=-2){
        frunzaMin=findMin(n);
       // cout<<frunzaMin<<endl;
        if (frunzaMin!=-2)
            prufer.push_back(tati[frunzaMin]);
        tati[frunzaMin]=-3;
    }
}
int main(int argc, char* argv[]){

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n;
    int x;
    fin>>n;
    for (int i=0; i<n; i++)
    {
        fin>>x;
        tati[i]=x;
        //cout<<tati[i]<<" ";
    }
    
    Prufer(n);
    fout<<prufer.size()<<'\n';
    for (int i=0; i<prufer.size(); i++)
        fout<<prufer[i]<<" ";

    return 0;
}
