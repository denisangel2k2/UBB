#include "Repository.h"
#include <iostream>
#include <string>

int Repository::add(const Masina& m)
{
	
	if (find(m.getID()))
		throw runtime_error("Masina exista!\n");

	this->lista.add(m);
	return 1;

}

int Repository::del(int id)
{
	auto it = lista.begin();
	while (it != lista.end() && id != (*it).getID()) {
		++it;
	}
	//auto it = find_if(lista.begin(), lista.end(), [=](const Masina& m) {return m.getID() == id; });
	if (it != lista.end()) {
		lista.erase(it);
		return 1;}
	else {
		throw runtime_error("Nu exista masina!\n");}}

int Repository::update(const Masina& m)
{
	auto it = lista.begin();
	while (it != lista.end() && m.getID() != (*it).getID()) {
		++it;
	}
	//auto it = find_if(lista.begin(), lista.end(), [&](const Masina& otm) {if (otm.getID() == m.getID()) return 1; else return 0; });

	if (it != lista.end()) {
		*it = m;
		return 1;}
	else {
		throw runtime_error("Nu exista masina!\n");}}

int Repository::find(int id)
{	
	for (int i = 0; i < lista.size(); i++)
		if (lista[i].getID() == id)
			return 1;
	return 0;
	/*
	auto it = find_if(lista.begin(), lista.end(), [=](const Masina& m) {return m.getID() == id; });
	if (it != lista.end())
		return 1;
	return 0;
	*/
}

const Masina& Repository::findCar(int id) 
{
	auto it = lista.begin();
	while (it != lista.end() && id != (*it).getID()) {
		++it;
	}
	//auto it = find_if(lista.begin(), lista.end(), [=](const Masina& m) {return m.getID() == id; });
	if (it != lista.end())
		return *it;
	else throw runtime_error("Nu exista masina!\n");}

size_t Repository::size() noexcept
{
	return this->lista.size();
}
const DynamicVector<Masina>& Repository::getAll() const
{
	return lista;
}
/*
const DynamicVector<Masina>& Repository::getAll() const
{
	return lista;
}
*/

