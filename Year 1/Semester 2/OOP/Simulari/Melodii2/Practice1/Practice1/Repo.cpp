#include "Repo.h"
#include <algorithm>
#include "Domain.h"
#include <fstream>
#include "Domain.h"
void Repo::readFromFile(string filepath)
{
	std::ifstream fin(filepath);
	if (fin.is_open()) {
		lista.clear();
		string input;
		while (getline(fin, input)) {
			char* s = (char*)input.c_str();
			char* p = strtok(s, " ");
			vector<string>parts;
			while (p != NULL) {
				parts.push_back(p);
				p = strtok(NULL, " ");
			}
			int id = stoi(parts[0]);
			string artist = parts[1];
			string titlu = parts[2];
			string gen = parts[3];
			Melodie m{ id,titlu,artist,gen };
			lista.push_back(m);
		}
		fin.close();
	}

}
void Repo::writeToFile(string filepath)
{
	std::ofstream fout(filepath);
	if (fout.is_open()) {
		for (const auto& el : lista)
			fout << el.getID() << " " << el.getArtist() << " " << el.getTitlu() << " " << el.getGen() << '\n';

		fout.close();
	}
}
void Repo::add(const Melodie& m)
{
	readFromFile(filepath);
	auto it = std::find_if(lista.begin(), lista.end(), [&](const Melodie& ot) {if (ot.getID() == m.getID()) return true; return false; });
	if (it != lista.end()) {
		string s = "Melodia exista!\n";
		throw RepoException{s};
	}
	lista.push_back(m);
	writeToFile(filepath);

}

void Repo::del(int id)
{
	readFromFile(filepath);
	auto it= std::find_if(lista.begin(), lista.end(), [=](const Melodie& ot) {if (ot.getID() == id) return true; return false; });
	if (it == lista.end()) {
		string s = "Melodia nu exista!\n";
		throw RepoException{ s };
	}
	lista.erase(it);
	writeToFile(filepath);
}

const vector<Melodie>& Repo::getAll() 
{
	readFromFile(filepath);
	std::sort(lista.begin(), lista.end(), [](const Melodie& m1, const Melodie& m2) {return m1.getArtist() < m2.getArtist(); });
	return lista;
	writeToFile(filepath);
}

int Repo::getMaxId()
{
	int idmax = 0;
	readFromFile(filepath);
	for (const auto& el : lista)
		idmax = std::max(idmax, el.getID());
	return idmax + 1;
}

const Melodie& Repo::find(int id)
{
	auto it = std::find_if(lista.begin(), lista.end(), [=](const Melodie& m) {return m.getID() == id; });
	if (it != lista.end())
		return *it;
	
}
