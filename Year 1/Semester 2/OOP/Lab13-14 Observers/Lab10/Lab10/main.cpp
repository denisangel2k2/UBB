#include "Lab10.h"
#include "GUI.h"
#include "Service.h"
#include "Repository.h"
#include "Valid.h"
#include "Tests.h"
#include <QtWidgets/QApplication>
void runGUI(int argc, char* argv[]) {
    
    QApplication a(argc, argv);
    FileRepository repo{ "repo.txt" };
    Valid valid;
    Service serv{ repo,valid };
    AdminService serv2{ repo,valid };
    GUI gui{ serv, serv2};
    gui.show();
    a.exec();
}
int main(int argc, char *argv[])
{
    Tests teste;
    teste.runTests();
    runGUI(argc,argv);
    return 0;
}
