//flux pompare
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

typedef struct {
	int h, e;
}nod;
std::queue<int> Q;
std::vector<std::vector<std::pair<int, int>>> rezid;
std::vector<bool> vf;
std::vector<nod> det;
int n, x, y, c, m,s,t;

void inaltare(int x) {
	det[x].h++;
}

void descarcare(int x) {
	while(det[x].e  > 0) {
		int cont = 0;
		int iter = 0;
		while(iter < rezid[x].size()) {
			int sw_sters = 0;
			if (det[x].e == 0)
				break;
			if (det[x].h == det[rezid[x][iter].first].h + 1) {
				//pompare
				int minim = std::min(rezid[x][iter].second, det[x].e);//minimul dintre excesul lui x si cat poate trimite pana la acel nod
				det[rezid[x][iter].first].e += minim;
				if (rezid[x][iter].first!=s && rezid[x][iter].first!=t && vf[rezid[x][iter].first] == 0) {//nodurile care nu se afla in coada pentru a fi 
					//verificate(la final ar avea exces dar cum nu sunt verificate nu se va distribui)
					Q.push(rezid[x][iter].first);
					vf[rezid[x][iter].first] = 1;
				}
				det[x].e -= minim;
				rezid[x][iter].second = rezid[x][iter].second - minim;

				int nr = rezid[x][iter].first;
				if (rezid[x][iter].second == 0) {
					sw_sters = 1;
					rezid[x].erase(rezid[x].begin() + iter);//stergem un arc dc acesta este 0 (flux maxim pe acest arc)
				}
				
				int ok = 0;
				for (auto& it2 : rezid[nr]) {
					if (it2.first == x) {
						ok = 1;
						it2.second += minim;
					}
				}
				if (ok == 0) {
					rezid[nr].push_back(std::make_pair(x, minim));//adaugam arcul invers in calea reziduala

				}
			}

			if (sw_sters == 0)
				iter++;
		}
		if(det[x].e > 0)
			inaltare(x);
	}
}

int main(int argc, char** argv) {
    std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);
	
	fin>>n>>m;
	rezid.resize(n);
	det.resize(n);
	vf.resize(n);
	for (int i = 1; i <=m ; i++) {
		fin >> x >> y >> c;
		rezid[x].push_back(std::make_pair(y, c));
	}

	//initializam
	for (int i = 1; i < n; i++) {
		det[i].e = 0;
		det[i].h = 0;
	}

	s = 0, t = n-1;
	det[s].h = n;

	for (auto& it : rezid[s]) {
		det[it.first].e = it.second;//nodurile legate de sursa primesc flux maxim
		det[s].e -= it.second;
		rezid[it.first].push_back(std::make_pair(s, it.second));
	}
	rezid[s].clear();

	for (int i = 1; i < n - 1; i++) {
		vf[i] = 1;
		Q.push(i);
	}

	//flux
	while (!Q.empty()) {
		int varf = Q.front();
		int old_h = det[varf].h;
		descarcare(varf);
		Q.pop();
		vf[varf] = 0;
		if (det[varf].h > old_h)
		{
			Q.push(varf);
			vf[varf] = 1;
		}
	}

	fout << det[t].e;
	return 0;
}
