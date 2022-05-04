#include "FileRepository.h"
#include <fstream>
#include <cstring>

using std::ifstream;
using std::ofstream;

void FileRepository::readFromFile()
{

	

	ifstream fin(filepath);
	
	if (fin.is_open()) {
		Repository::lista.clear(); // Repository::clearRepo();
		string input;

		while (getline(fin, input)) {
			//daca linia citita nu e goala
			if (input != "") {
				//convertesc linia la cstring ca sa pot sa fac strtok
				char* s = (char*)input.c_str();
				//fac strtok pe cstringul linie
				char* p;

				p = strtok(s, ",");
				vector<string>parts;

				while (p != NULL) {
					parts.push_back(p);//bag fiecare data intr-un vector de stringuri
					p = strtok(NULL, ",");
				}
				//salvez datele in variabile
				int id = stoi(parts[0]);
				string nrInm = parts[1];
				string prod = parts[2];
				string model = parts[3];
				string tip = parts[4];
				//construiesc obiectul (masina)

				Masina m{ id,nrInm,prod,model,tip };
				Repository::add(m);
			}
		}
	}
	
	fin.close();
}

void FileRepository::writeToFile()
{
	ofstream fout(filepath);

	

	if (fout.is_open()) {
		for (const auto& masina : getAll()) {
			//fout << masina;
			fout << to_string(masina.getID()) << "," << masina.getNrInmatriculare() << "," << masina.getProducator() << "," << masina.getModel() << "," << masina.getTip() << '\n';

		}
	}
		

	
	
	fout.close();
	
}



int FileRepository::add(const Masina& m)
{
	readFromFile();
	Repository::add(m);
	writeToFile();
	return 1;
}

int FileRepository::del(int id)
{
	readFromFile();
	Repository::del(id);
	writeToFile();
	return 1;
}

int FileRepository::update(const Masina& m)
{
	readFromFile();
	Repository::update(m);
	writeToFile();
	return 1;
}
