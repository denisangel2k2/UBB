#pragma once
#include "Domain.h"
#include <vector>
#include <string>
using namespace std;

class Exceptions {
public:
	string getEx(const vector<string>& ex);
};

class Valid
{
private:

public:
	bool validateID(int id);
	bool validate(Masina& masina);
};

