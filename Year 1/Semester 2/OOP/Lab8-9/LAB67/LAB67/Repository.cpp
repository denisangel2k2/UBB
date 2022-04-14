#include "Repository.h"
#include <iostream>
#include <string>

int Repository::add_fictiv(const Masina& m)
{
	/*
	auto it = find_if(lista_fictiva.begin(), lista_fictiva.end(), [&](const Masina& ot) {
		if (ot.getID() == m.getID())
			return 1;
		else return 0; });

		if (it != lista_fictiva.end())
			throw runtime_error("Masina exista!\n");
		*/
	this->lista_fictiva.push_back(m);
	return 1;
}

int Repository::add(const Masina& m)
{
	
	if (find(m.getID()))
		throw runtime_error("Masina exista!\n");

	this->lista.push_back(m);
	return 1;
}
const size_t Repository::getNumberOfCars() const{
	return lista.size();
}
void Repository::clearRepoFictiv()
{
	lista_fictiva.clear();
}
void Repository::clearRepo()
{
	lista.clear();
}
int Repository::del(int id)
{
	auto it = find_if(lista.begin(), lista.end(), [=](const Masina& m) {return m.getID() == id; });
	if (it != lista.end()) {
		lista.erase(it);
		return 1;}
	else {
		throw runtime_error("Nu exista masina!\n");}}

int Repository::update(const Masina& m)
{
	auto it = find_if(lista.begin(), lista.end(), [&](const Masina& otm) {if (otm.getID() == m.getID()) return 1; else return 0; });

	if (it != lista.end()) {
		*it = m;
		return 1;}
	else {
		throw runtime_error("Nu exista masina!\n");}}

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
	else throw runtime_error("Nu exista masina!\n");}

size_t Repository::size() noexcept
{
	return this->lista.size();
}

const size_t Repository::sizeAdmin() noexcept
{
	return this->lista_fictiva.size();
}

const vector<Masina>& Repository::getAll() const
{
	return lista;
}

const vector<Masina>& Repository::getAllFictiv() const
{
	return this->lista_fictiva;
}
