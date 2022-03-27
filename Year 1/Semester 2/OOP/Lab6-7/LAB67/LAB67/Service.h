#pragma once
#include "Repository.h"
#include "Valid.h"
#include "Domain.h"
#include <functional>

class Service
{
private:
	Repository repo;
	Valid valid;

public:
	Service(const Repository& rep, const Valid& valid) :repo{ rep }, valid{ valid }{}

	int srv_add(int id, const string& nrI, const string& prod, const string& model, const string& tip);
	int srv_del(int id);
	int srv_update(int id, const string& nrI, const string& prod, const string& model, const string& tip);

	const Masina& srv_findCar(int id) const;
	vector<Masina> filter(const string& what, int whichFilter);
	vector<Masina>sort(function<bool(const Masina& m1, const Masina& m2)>compareFunction);

	vector<Masina> srv_getAll();
	


};

