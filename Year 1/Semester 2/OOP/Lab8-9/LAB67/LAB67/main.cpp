#include <iostream>
#include "Repository.h"
#include "Service.h"
#include "UI.h"
#include "Tests.h"
#include "Valid.h"
#include <random>
#include <chrono> 
#include "AdminService.h"


using namespace std;

int main() {


	Tests teste;
	teste.runTests();

	Repository repo;
	Valid valid;
	Service serv{ repo, valid };
	AdminService serv2{ repo,valid };
	UI ui{ serv, serv2};
	ui.run();


	return 0;
}