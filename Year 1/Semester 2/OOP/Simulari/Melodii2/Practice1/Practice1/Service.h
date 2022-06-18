#pragma once
#include "Repo.h"
#include "Valid.h"
#include "Observer.h"
class Service : public Observable
{
private:
	Repo& repo;
	Valid& valid;
	int id_global;
public:
	Service(Repo& r, Valid& v) : repo{ r }, valid{ v }{ id_global = repo.getMaxId(); }
	void srv_add(string titlu, string artist, string gen);
	void srv_del(int id);
	const Melodie& find(int id);
	const vector<Melodie>& getAll();
};

