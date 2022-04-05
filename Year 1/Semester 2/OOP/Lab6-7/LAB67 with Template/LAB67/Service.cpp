#include "Service.h"
#include <iostream>
#include <iterator>
#include <algorithm>

Service::Service(Repository& rep, Valid& _valid) :repo{rep},valid{_valid} {}

int Service::srv_add(int id, const string& nrI, const string& prod, const string& model, const string& tip)
{
	Masina m{ id,nrI,prod,model,tip };
	valid.validate(m);
	return repo.add(m);
}

int Service::srv_del(int id)
{
	if (!valid.validateID(id))
		throw runtime_error("ID invalid!\n");
	return repo.del(id);
}

int Service::srv_update(int id, const string& nrI, const string& prod, const string& model, const string& tip)
{
	Masina m{ id,nrI,prod,model,tip };
	valid.validate(m);
	return repo.update(m);
}

const Masina& Service::srv_findCar(int id) const
{
	return repo.findCar(id);
}
DynamicVector<Masina> Service::filter(const string& what, int whichFilter) const
{
	DynamicVector<Masina>v1;
	DynamicVector<Masina>v2;

	v1 = repo.getAll();
	if (whichFilter == 1) {
		for (const auto& el : v1)
			if (el.getProducator() == what)
				v2.add(el);
		
	}
	else if (whichFilter == 2) {
		for (const auto& el : v1) {
			if (el.getTip() == what)
				v2.add(el);
		}
	}
	return v2;

}
//
/*
DynamicVector<Masina> Service::filter(const string& what, int whichFilter) const
{
	DynamicVector<Masina>v1;
	DynamicVector<Masina> v2;
	v1 = repo.getAll();
	if (whichFilter == 1) {
		copy_if(v1.begin(), v1.end(),back_inserter(v2), [&](const Masina& m) {return m.getProducator() == what; });
	}
	else if (whichFilter == 2) {
		for (const auto& el : v1) {
			if (el.getTip() == what)
				v2.push_back(el);
		}
	}
	return v2;
	
}
*/
DynamicVector<Masina> Service::sort(function<bool(const Masina& m1, const Masina& m2)>compareFunction) const
{
	DynamicVector<Masina>v = repo.getAll();
	for (auto& el1 : v)
		for (auto& el2 : v)
			if (compareFunction(el1, el2))
				swap(el1, el2);
	return v;
}
/*
DynamicVector<Masina> Service::sort(function<bool(const Masina& m1, const Masina& m2)>compareFunction) const
{
	DynamicVector<Masina>v = repo.getAll();

	for (auto& el1 : v)
		for (auto& el2 : v)
			if (compareFunction(el1, el2))
				swap(el1, el2);

	return v;
}
*/
DynamicVector<Masina> Service::srv_getAll() const
{
	return repo.getAll();
}
/*
DynamicVector<Masina> Service::srv_getAll() const
{
	return repo.getAll();
}
*/




