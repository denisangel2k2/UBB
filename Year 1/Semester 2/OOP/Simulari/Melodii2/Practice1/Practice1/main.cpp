#include "Practice1.h"
#include <QtWidgets/QApplication>
#include "Repo.h"
#include "Service.h"
#include "GUI.h"
#include "Valid.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo r{ "muzica.txt" };
    Valid val;
    Service srv{r,val};
    GUI gui{ srv };
    gui.show();
    return a.exec();
}
