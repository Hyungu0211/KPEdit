#include "KPEdit.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    KPEdit window;
    window.show();
    return app.exec();
}
