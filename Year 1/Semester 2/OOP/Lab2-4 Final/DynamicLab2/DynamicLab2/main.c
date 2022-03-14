#include <stdio.h>
#include "tests.h"
#include <crtdbg.h>
#include "domain.h"
#include "vectordynamic.h"
#include "repo.h"
#include "service.h"
#include "ui.h"

int main() {

	
	runTests();

	Repository* repo = createRepo(10);
	Service* serv = createService(repo);
	UI* ui = createUI(serv);
	
	UI_RUN(ui);

	_CrtDumpMemoryLeaks();
	return 0;

}