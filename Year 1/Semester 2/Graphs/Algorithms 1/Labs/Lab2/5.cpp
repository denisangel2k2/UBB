#include <bits/stdc++.h>

using namespace std;
ifstream fin("graf5.txt");

void read(vector<vector<int>>&mat, int& istart, int& jstart, int& istop,int& jstop){ 
    char x;
    vector<int>temp;
    int linie=0, coloana=0;
    while(fin.get(x)){ 
        if (x!='\n'){ 
            if (x=='1')
                temp.push_back(-1);
            else if (x==' ')
                temp.push_back(0);
            else if (x=='S'){ 
                temp.push_back(1);
                istart=linie;
                jstart=coloana;
            }
            else if (x=='F'){
                temp.push_back(0); 
                istop=linie;
                jstop=coloana;
            }
            coloana++;
        }
        else {
            mat.push_back(temp); 
            temp.clear();
            coloana=0;
            linie++;
        }
    }
}
bool verifica(int i, int j, int n, int m){ 
    if (i<0 || i>=n || j<0 || j>=m)
        return false;
    return true;
}
void lee(vector<vector<int>>&v,int istart, int jstart, int istop, int jstop){ 
    deque<pair<int,int>>q;
    q.push_back(make_pair(istart,jstart));
    int di[]={ 0, 0, 1, -1};
    int dj[]={ 1, -1, 0, 0};

    while(!q.empty()){ 
        int I=q.front().first;
        int J=q.front().second;
        q.pop_front();
        for (int d=0; d<4; d++){ 
            int iv=I+di[d];
            int jv=J+dj[d];

            if (verifica(iv,jv,v.size(),v[0].size()) && v[iv][jv]==0){ 
                q.push_back(make_pair(iv,jv));
                v[iv][jv]=v[I][J]+1;
            }
        }
    }
}
//void invers(vector<vector<int>>&v)
int main(){ 

    vector<vector<int>>mat;
    int istart,jstart,istop,jstop;

    read(mat,istart,jstart,istop,jstop);
     
    //int n=mat.size();
    //int m=mat[0].size();
    cout<<mat[istart][jstart]<<endl;
    lee(mat,istart,jstart,istop,jstop);
    for (auto linie:mat){ 
        for (auto el:linie){ 
            if (el==-1)
               cout<<'x';
            else cout<<el<<" ";
        }
        cout<<'\n';
    } 
    return 0;

}
