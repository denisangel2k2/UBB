#include <iostream>
#include "Repository.h"
#include "Service.h"
#include <crtdbg.h>
#include "UI.h"
#include "Tests.h"
#include "Valid.h"


using namespace std;

int main() {

	if (true) {
		Tests teste;
		teste.runTests();
		
		Repository repo;
		Valid valid;
		Service serv{ repo, valid };
		UI ui{ serv };
		ui.run();
		
	}

	_CrtDumpMemoryLeaks();

	return 0;
}