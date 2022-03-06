#include <stdio.h>
#include "ui.h"
#include "repo.h"
#include "service.h"
#include "ui.h"
#include <crtdbg.h>
#include "domain.h"
#include <string.h>
#include "teste.h"


int main() {

	RunTests();
	Repository* repo = createRepo(1);
	Service* serv = createService(repo);
	UI* ui = createUI(serv);
	UI_RUN(ui);

	_CrtDumpMemoryLeaks();

	return 0;
}