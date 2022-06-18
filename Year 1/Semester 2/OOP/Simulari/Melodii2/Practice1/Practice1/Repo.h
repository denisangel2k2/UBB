#pragma once
#include <string>
#include <vector>
#include "Domain.h"
using std::vector;
using std::string;
class Repo
{
private:
	string filepath;
	vector<Melodie> lista;
	void readFromFile(string filepath);
	void writeToFile(string filepath);
public:
	Repo(string fil) : filepath{ fil } { readFromFile(filepath); }
	void add(const Melodie& m);
	void del(int id);
	const vector<Melodie>& getAll() ;
	int getMaxId();
	const Melodie& find(int id);

};

