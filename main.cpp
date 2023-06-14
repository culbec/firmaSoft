#include <QApplication>
#include "./headers/GUI.h"
#include "tester.h"

int main(int argc, char *argv[]) {
    QApplication app{argc, argv};

    tester tester;
    tester.testEntity();
    tester.testRepo();
    tester.testService();

    Repository repository{"repo.txt"};
    Service service{repository};

    mainWindow mainWnd{service};

    return QApplication::exec();
}
