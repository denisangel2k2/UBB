#pragma once
#include <vector>
#include <string>
#include "Domain.h"
using namespace std;

class Repository
{

private:

	vector<Masina>lista;

public:
	int add(const Masina& m);
	int del(int id);
	int update(const Masina& m);
	int find(int id);
	const Masina& findCar(int id) const; 

	vector<Masina> getAll() const;
};

