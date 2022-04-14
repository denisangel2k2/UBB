#pragma once
#include "Repository.h"
#include "Service.h"
#include "Valid.h"
class AdminService
{
private:
	Repository& repo;
	Valid& valid;

public:
	AdminService(Repository& _repo, Valid& _val) : repo{ _repo }, valid{ _val } {}

	int srv_add_fictiv(int id, const string& nrI, const string& prod, const string& model, const string& tip);
	
	const size_t srv_getNumberOfCars() const;
	int srv_add(const string& nrI);
	void srv_clearRepo();
	const vector<Masina>& srv_getall();
	int addRandom(int numberToAdd);

};

