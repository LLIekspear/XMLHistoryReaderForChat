#include "mainwindow.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setOrganizationName("Frolov Oleg SKB201");
    app.setApplicationName("XML-Reader");

    MainWindow w;
    w.show();
    return app.exec();
}
