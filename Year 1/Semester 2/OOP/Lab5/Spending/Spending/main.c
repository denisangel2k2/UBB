#include <stdio.h>
#include <crtdbg.h>
#include "spending.h"
#include "repository.h"
#include "service.h"
#include "ui.h"
#include "vectordynamic.h"

int main() {
    test_domain();
    test_repository();
    test_service();
    test_vector();
    repository* repo = create_repository();
    service* srv = create_service(repo);
    ui_type* ui = create_ui(srv);
    ui_run(ui);
    delete_ui(ui);

    _CrtDumpMemoryLeaks();
}
