#include "Service.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>
#include "Exceptii.h"


using std::vector;

Service::Service(Repository& _rep, Valid& _valid) : repo{ _rep }, valid{ _valid }{}



int Service::srv_add(int id, const string& nrI, const string& prod, const string& model, const string& tip)
{
	Masina m{ id,nrI,prod,model,tip };
	valid.validate(m);

	repo.add(m);
	undoActions.push_back(make_unique<UndoAdd>(m, repo));
	return 1;
}



int Service::srv_del(int id)
{
	if (!valid.validateID(id))
		throw runtime_error("ID invalid!\n");

	Masina m = repo.findCar(id);
	repo.del(id);
	undoActions.push_back(make_unique<UndoDelete>(m, repo));
	return 1;
}

int Service::srv_update(int id, const string& nrI, const string& prod, const string& model, const string& tip)
{
	Masina m{ id,nrI,prod,model,tip };
	valid.validate(m);
	
	try {
		Masina m_init = repo.findCar(id);
		undoActions.push_back(make_unique<UndoUpdate>(m_init, repo));
	}
	catch (const exception&) {}
	repo.update(m);
	return 1;
}

const Masina& Service::srv_findCar(int id) const
{
	return repo.findCar(id);
}
//
vector<Masina> Service::filter(const string& what, int whichFilter) const
{
	vector<Masina>v1;
	vector<Masina>v2;
	v1 = repo.getAll();
	if (whichFilter == 1) {
		copy_if(v1.begin(), v1.end(),back_inserter(v2), [&](const Masina& m) {return m.getProducator() == what; });
	}
	else if (whichFilter == 2) {
		copy_if(v1.begin(), v1.end(), back_inserter(v2), [&](const Masina& m) {return m.getTip() == what; });
	}
	return v2;
	
}

vector<Masina> Service::sort(function<bool(const Masina& m1, const Masina& m2)>compareFunction) const
{
	vector<Masina>v = repo.getAll();
	std::sort(v.begin(), v.end(), compareFunction);
		/*
	for (auto& el1 : v)
		for (auto& el2 : v)
			if (compareFunction(el1, el2))
				swap(el1, el2);
*/
	return v;
}

vector<Masina> Service::srv_getAll() const
{
	return repo.getAll();
	
}

const size_t Service::srv_getNumberOfCars() const
{
	return repo.getNumberOfCars();
}

int Service::srv_add(const string& nrI)
{
	std::mt19937 mt{ std::random_device{}() };
	int numarMasini = (int)srv_getNumberOfCars();
	std::uniform_int_distribution<> dist(numarMasini, numarMasini+1000);
	int rndNr = dist(mt);

	int id = rndNr;
	string prod;
	string model;
	string tip;

	prod = "Prod" + to_string(id);
	model = "Model" + to_string(id);
	tip = "Tip" + to_string(id);

	id = dist(mt);
	srv_add(id, nrI, prod, model, tip);

	return 1;

}
void Service::srv_clearRepo()
{
	repo.clearRepo();
}
/*
int Service::addRandom(int numberToAdd)
{
	int rndNr=1;
	int numarInvalide = -1;
	int odata = 0;
	for (int i = 1; i <= numberToAdd; i++) {

		std::mt19937 mt{ std::random_device{}() };
		int numarMasini = (int)srv_getNumberOfCars();
		std::uniform_int_distribution<> dist(numarMasini, numarMasini + numberToAdd+100);
		rndNr = dist(mt);

		string prod;
		string model;
		string tip;
		string nrI;

		prod = "Prod" + to_string(rndNr);
		model = "Model" + to_string(rndNr);
		tip = "Tip" + to_string(rndNr);
		nrI = "Numar Inm." + to_string(rndNr);
		
		try {
			if (odata == 0) {
				odata = 1;
				srv_add(-1, nrI, prod, model, tip);
			}
			srv_add(rndNr, nrI, prod, model, tip);
		}
		catch (const exception&) {
			numarInvalide++;
		}
	}
	return numarInvalide;
	
}
*/
int Service::addRandom(int numberToAdd)
{
	int rndNr = 1;
	int odata = 0;
	int cateAdaugate = 0;

	string prod;
	string model;
	string tip;
	string nrI;

	while (cateAdaugate < numberToAdd) {

		std::mt19937 mt{ std::random_device{}() };
		int numarMasini = (int)srv_getNumberOfCars();
		std::uniform_int_distribution<> dist(numarMasini, numarMasini + numberToAdd * 2);


		try {
			rndNr = dist(mt);
			prod = "Prod" + to_string(rndNr);
			model = "Model" + to_string(rndNr);
			tip = "Tip" + to_string(rndNr);
			nrI = "Numar Inm." + to_string(rndNr);

			if (odata == 0) {
				odata = 1;
				srv_add(-1, nrI, prod, model, tip);
			}

			srv_add(rndNr, nrI, prod, model, tip);
			cateAdaugate++;
		}
		catch (const exception&) {}
		
	}
	return 1;
}

void Service::undo()
{

	if (undoActions.size() == 0)
		throw Exceptie{ "Nu se poate efectua undo!\n" };
	
	undoActions.back()->doUndo();
	undoActions.pop_back();

}




