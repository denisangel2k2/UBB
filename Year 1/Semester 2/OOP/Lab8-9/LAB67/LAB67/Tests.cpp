#include "Tests.h"
#include "Domain.h"
#include "Valid.h"
#include <string>
#include "Exceptii.h"
#include "Repository.h"
#include "Service.h"
#include <assert.h>
#include <iostream>
#include <fstream>
using namespace std;

void Tests::runTests()
{
	testDomain();
	testService();
	testRepo();
	
}

void Tests::testDomain()
{
	constexpr int id = 1;
	string nrI{ "AR303ZDD" };
	string prod{ "Ford" };
	string model{"Focus"};
	string tip{"SUV"};
	Valid validator;
	Masina m{ id,nrI,prod,model,tip };

	assert(m.getID() == id);
	assert(m.getModel() == model);
	assert(m.getNrInmatriculare() == nrI);
	assert(m.getProducator() == prod);
	assert(m.getTip() == tip);
	assert(validator.validate(m));
	Masina m2{-1,"a","a","a","a"};
		
	try {
		validator.validate(m2);
	}
	catch (const exception& ex) {
		string s = ex.what();
		assert(s == "ID invalid!\nModel invalid!\nNr. inmatriculare invalid!\nProducator invalid!\nTip invalid!\n");
	}
	m2=Masina{ 1,"a","a","a","a" };
	m2.setModel(m.getModel());
	m2.setNrInmatriculare(m.getNrInmatriculare());
	m2.setProducator(m.getProducator());
	m2.setTip(m.getTip());
	
	assert(m == m2);

	ofstream fout("test.csv");
	fout << m << endl;
}

void Tests::testService()
{
	testCreateServ();
	testServAdd();
	testServDelete();
	testServUpdate();
	testServFilter();
	testServSort();
	testServGetAll();
	testServAdd2();
	testSrvClearRepo();
	testSrvAddRandom();
	testUndo();
}

void Tests::testCreateServ()
{
	Repository repo;
	Valid val;
	Service const serv{ repo, val };
	
	assert(repo.size() == 0);


}

void Tests::testServAdd()
{
	Repository repo;
	Valid val;
	Service serv{ repo , val};
	constexpr int id = 1;
	string nrI = "iai";
	string prodd = "pap";
	string model = "mam";
	string tip = "tit";

	Masina m1{id,nrI,prodd,model,tip};
	assert(m1.getProducator() == prodd);
	repo.add(Masina{ id,nrI,prodd,model,tip });



	assert(repo.size() == 1);
	try {
		serv.srv_add(id, nrI, prodd, model, tip);
	}
	catch (const exception& ex) {
		string exc = ex.what();
		assert(exc == "Masina exista!\n");
	}

}

void Tests::testServAdd2()
{
	Repository repo;
	Valid val;
	Service serv{ repo , val };

	string nrI = "iai";


	
	serv.srv_add(nrI);
	assert(serv.srv_getNumberOfCars() == 1);
	
	try {
		serv.srv_add("");
	}
	catch (const exception& ex) {
		string exc = ex.what();
		assert(exc=="Nr. inmatriculare invalid!\n");
	}


	
}

void Tests::testServDelete()
{
	Repository repo;
	Valid val;
	Service serv{ repo , val };

	constexpr int id = 1;
	string nrI = "iai";
	string prod = "pap";
	string model = "mam";
	string tip = "tit";

	repo.add(Masina{ id,nrI,prod,model,tip });
	assert(repo.size()==1);

	serv.srv_del(1);
	assert(repo.size() == 0);

	try {
		serv.srv_del(1);
	}
	catch (const exception& ex) {
		string exc = ex.what();
		assert(exc == "Nu exista masina!\n");
	}
	try {
		serv.srv_del(-1);
	}
	catch (const exception& ex) {
		string exc = ex.what();
		assert(exc == "ID invalid!\n");
	}

}

void Tests::testServUpdate()
{
	Repository repo;
	Valid val;
	Service serv{ repo , val };

	constexpr int id = 1;
	string nrI = "iai";
	string nrI2 = "ddd";
	string prod = "pap";
	string model = "mam";
	string tip = "tit";


	repo.add(Masina{ id,nrI,prod,model,tip });
	assert(repo.size() == 1);

	serv.srv_update(1, nrI2, prod, model, tip);

	Masina m = serv.srv_findCar(1);
		
	assert(m.getNrInmatriculare() == "ddd");

	try {
		m = serv.srv_findCar(2);
	}
	catch (const exception& ex) {
		string s = ex.what();
		assert(s == "Nu exista masina!\n");
	}

	try {
		serv.srv_update(2, nrI2, prod, model, tip);
	}
	catch (const exception& ex) {
		string s = ex.what();
		assert(s == "Nu exista masina!\n");
	}
}

void Tests::testServFilter()
{

	Repository repo;
	Valid val;
	Service serv{ repo , val };

	constexpr int id = 1;
	string nrI = "iai";
	string prod = "pap";
	string model = "mam";
	string tip = "tit";

	serv.srv_add(id, nrI, prod, model, tip);
	string what = "pap";
	assert(repo.size() == 1);
	vector<Masina>v = serv.filter(what, 1);



	assert(v.size() == 1);
	what = "tit";
	v = serv.filter(what, 2);

	assert(v.size() == 1);


}

void Tests::testServSort()
{

	Repository repo;
	Valid val;
	Service serv{ repo , val };

	constexpr int id = 1;
	string nrI = "iai";
	string prod = "pap";
	string nrI2 = "aaa";
	string model = "mam";
	string tip = "tit";

	serv.srv_add(id, nrI, prod, model, tip);
	serv.srv_add(2, nrI2, prod, model, tip);

	vector<Masina>v = serv.sort([](const Masina& m1, const Masina& m2) {if (m1.getNrInmatriculare() < m2.getNrInmatriculare()) return true; else return false; });
	assert(v.size() == 2);
	v = serv.sort([](const Masina& m1, const Masina& m2) {if (m1.getTip() < m2.getTip()) return true; else return false; });
	assert(v.size() == 2);
	serv.addRandom(100);
	v= serv.sort([](const Masina& m1, const Masina& m2) {
		if (m1.getProducator() < m2.getProducator())
			return true;
		else if (m1.getProducator() == m2.getProducator())
			if (m1.getModel() < m2.getModel())
				return true;
			else return false;
		else return false;
		});
	assert(v.size() == 102);

	Exceptie r{ "exceptie test" };
	assert(r.getMessage() == "exceptie test");
}

void Tests::testServGetAll()
{
	Repository repo;
	Valid val;
	Service serv{ repo , val };

	constexpr int id = 1;
	string nrI = "iai";
	string prod = "pap";
	string model = "mam";
	string tip = "tit";

	serv.srv_add(id, nrI, prod, model, tip);
	vector<Masina>v = serv.srv_getAll();
	assert(v.size() == 1);

}

void Tests::testRepo()
{
	Repository repo;
	Masina m{ 1,"","","","" };
	repo.add(m);
	assert(repo.size() == 1);
	repo.clearRepo();
	assert(repo.size() == 0);

	repo.add_fictiv(m);
	assert(repo.sizeAdmin() == 1);
	repo.clearRepoFictiv();
	vector<Masina>v = repo.getAllFictiv();
	try {
		repo.del(13);
	}
	catch (const exception& ex) {
		string exceptie = ex.what();
		assert(exceptie == "Nu exista masina!\n");
	}
	
}

void Tests::testSrvClearRepo()
{
	
	Valid val;
	Repository repo;
	Service serv{repo,val};
	Masina m{ 1,"","","","" };
	repo.add(m);
	assert(repo.size() == 1);
	serv.srv_clearRepo();
	assert(repo.size() == 0);
}

void Tests::testSrvAddRandom()
{
	Valid val;
	Repository repo;
	Service serv{ repo,val };

	serv.addRandom(100);
	
	assert(repo.size() == 100);

}

void Tests::testUndo()
{
	FileRepository repo{ "testrepo.txt" };
	Valid valid;
	Service srv{ repo,valid };
	ofstream fout("testrepo.txt");
	fout << "";
	if (fout.is_open()) {
		constexpr int id = 1;
		string nrI = "iai";
		string prod = "pap";
		string model = "mam";
		string tip = "tit";

		srv.srv_add(id, nrI, prod, model, tip);
		srv.undo();
		assert(repo.size() == 0);

		srv.srv_add(id, nrI, prod, model, tip);
		srv.srv_update(id, "sad", prod, model, tip);
		srv.undo();
		assert(srv.srv_findCar(id).getNrInmatriculare() == nrI);

		srv.srv_del(id);
		srv.undo();
		assert(repo.size() == 1);

		try {
			srv.undo();
			srv.undo();
		}
		catch (const Exceptie& ex) {
			assert(ex.getMessage() == "Nu se poate efectua undo!\n");
		}
	}
	fout.close();
	

}
