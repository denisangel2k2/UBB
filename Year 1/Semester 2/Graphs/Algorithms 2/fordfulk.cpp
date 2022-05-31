// C++ program for implementation of Ford Fulkerson
// algorithm
#include <bits/stdc++.h>

using namespace std;

const int sz=1005;
// Number of vertices in given graph
int graph[sz][sz];
int rGraph[sz][sz];
int V,E;
bool bfs(int s, int t, int parent[]){
    bool visited[1005];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(int v = 0; v < V; v++){
            if(visited[v] == false && rGraph[u][v] > 0){
                if(v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

int fordFulkerson(int graph[sz][sz],int s, int t)
{
    
    for(int u = 0; u < t + 1; u++)
        for(int v = 0; v < t + 1; v++)
            rGraph[u][v] = graph[u][v];

    int parent[1005];
    int max_flow = 0;

    while(bfs(s, t, parent)){
        int path_flow = INT_MAX;
        for(int v = t; v != s; v = parent[v]){
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        for(int v = t; v != s; v = parent[v]){
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}


int main(int argc,char* argv[])
{

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    int x,y,c; 
    fin>>V>>E;
    for (int i=0; i<E; i++){
        fin>>x>>y>>c;
        cout<<x<<y<<c<<endl;
        graph[x][y]=c;
    }
    int s=0;
    int t=V-1;
    fout<<fordFulkerson(graph,s,t);
	return 0;
}
