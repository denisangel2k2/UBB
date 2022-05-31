//kruskal
#include <iostream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int n, m, cost, ri, rj;
struct muchie
{
    int x, y, c;
};
vector <muchie> v;
vector <muchie> f;
vector <int> rang;
vector <int> t;
bool ok(muchie  x, muchie y)
{
    return x.c < y.c;
}

bool ok2(muchie x, muchie y) {
    if (x.x != y.x)
        return x.x < y.x;
    return x.y < y.y;
}

int radacina(int k)
{
    if (t[k] == 0)
        return k;
    else
    {
        int x = radacina(t[k]);
        t[k] = x;
        return x;
    }
}

void kruskal()
{
    int j = -1;
    for (int i = 1; i < n; i++)
    {
        do
        {
            j++;
            ri = radacina(v[j].x);
            rj = radacina(v[j].y);
        } while (ri == rj);
        cost += v[j].c;
        f[i - 1].x = v[j].x;
        f[i - 1].y = v[j].y;
        if (rang[ri] > rang[rj])
        {
            t[rj] = ri;
        }
        else
        {
            t[ri] = rj;
            if (rang[ri] == rang[rj])
                rang[rj]++;
        }
    }
}
int main(int argc, char** argv)
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    fin >> n >> m;
    v.resize(m);
    t.resize(n + 2);
    rang.resize(n + 2);
    f.resize(n - 1);
    for (int i = 0; i < m; i++)
        fin >> v[i].x >> v[i].y >> v[i].c;
    sort(v.begin(), v.end(), ok);
    kruskal();
    fout << cost << '\n' << f.size() << '\n';
    sort(f.begin(), f.end(), ok2);
    for (int i = 0; i < f.size(); i++)
        fout << f[i].x << " " << f[i].y << '\n';
    return 0;
}