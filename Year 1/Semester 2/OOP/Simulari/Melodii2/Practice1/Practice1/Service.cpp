#include "Service.h"

void Service::srv_add(string titlu, string artist, string gen)
{
	Melodie m{ id_global,titlu,artist,gen };
	valid.validate(m);
	repo.add(m);
	id_global++;
	notify();
}

void Service::srv_del(int id)
{
	Melodie m{ id,"","","folk" };
	valid.validate(m);
	repo.del(id);
	notify();
}

const vector<Melodie>& Service::getAll()
{
	return repo.getAll();
}

const Melodie& Service::find(int id)
{
	return repo.find(id);
}
