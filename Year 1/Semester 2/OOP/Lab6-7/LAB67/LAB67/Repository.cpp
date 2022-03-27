#include "Repository.h"
#include <iostream>
#include <string>

int Repository::add(const Masina& m)
{
	
	if (find(m.getID()))
		throw runtime_error("Masina exista!\n");

	this->lista.push_back(m);
	return 1;
}

int Repository::del(int id)
{
	auto it = find_if(lista.begin(), lista.end(), [=](const Masina& m) {return m.getID() == id; });
	if (it != lista.end()) {
		lista.erase(it);
		return 1;
	}
	else {
		throw runtime_error("Nu exista masina!\n");
	}

}

int Repository::update(const Masina& m)
{
	auto it = find_if(lista.begin(), lista.end(), [&](const Masina& otm) {if (otm.getID() == m.getID()) return 1; });

	if (it != lista.end())
		*it = m;
	else {
		throw runtime_error("Nu exista masina!\n");
	}
}

int Repository::find(int id)
{
	auto it = find_if(lista.begin(), lista.end(), [=](const Masina& m) {return m.getID() == id; });
	if (it != lista.end())
		return 1;
	return 0;
}

const Masina& Repository::findCar(int id) const
{
	auto it = find_if(lista.begin(), lista.end(), [=](const Masina& m) {return m.getID() == id; });
	if (it != lista.end())
		return *it;
	else throw runtime_error("Nu exista masina!\n");
}

vector<Masina> Repository::getAll() const
{
	return lista;
}
