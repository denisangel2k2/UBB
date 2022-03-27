#include "Tests.h"
#include "Domain.h"
#include "Valid.h"
#include <string>
#include <assert.h>
#include <iostream>
using namespace std;

void Tests::runTests()
{
	testDomain();
}

void Tests::testDomain()
{
	int id = 1;
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
	catch (exception& ex) {
		string s = ex.what();
		assert(s == "ID invalid!\nModel invalid!\nNr. inmatriculare invalid!\nProducator invalid!\nTip invalid!\n");
	}
	



}
