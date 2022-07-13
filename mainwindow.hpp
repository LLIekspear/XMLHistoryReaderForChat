#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtWidgets/QMainWindow>
#include <QDomElement>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_selectXMLButton_clicked();

private:
    Ui::MainWindow *ui;
    QDomDocument domDoc;

};
#endif // MAINWINDOW_HPP
