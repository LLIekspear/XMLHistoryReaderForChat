#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("XMLLogsReader");

}

void MainWindow::on_selectXMLButton_clicked() {
    ui->messageList->clear();
    QString path=QFileDialog::getOpenFileName(this, tr("Open Logs"), "/home/user/Desktop/", tr("XML Files (*.xml)"));
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)) {
        if(domDoc.setContent(&file)) {
            QDomElement topElement=domDoc.documentElement();
            QDomNode domNode=topElement.firstChild();
            while(!domNode.isNull()) {
                QDomElement domElement=domNode.toElement();
                if(domElement.tagName()=="log") {
                    QDomNode node=domElement.firstChild();
                    while(!node.isNull()) {
                        QDomElement element=node.toElement();
                        if(!element.isNull()) {
                            QString log;
                            QString tagName(element.tagName());
                            if(tagName=="name") {
//                                qDebug()<<"Name is: "<<element.text();
                                log.append("<strong>"+element.text()+"</strong>: ");
                                if(node.nextSiblingElement().tagName()=="ip") {
                                    log.prepend("["+node.nextSiblingElement().text()+"] ");
//                                    qDebug()<<"IP is: "<<node.nextSiblingElement().text();
                                }
                                if(node.nextSibling().nextSiblingElement().tagName()=="dateAndTime") {
                                    log.prepend(node.nextSibling().nextSiblingElement().text());
                                }
                                if(node.nextSibling().nextSibling().nextSiblingElement().tagName()=="message") {
                                    log.append(node.nextSibling().nextSibling().nextSiblingElement().text());
                                    ui->messageList->append(log);
                                } else if(node.nextSibling().nextSibling().nextSiblingElement().tagName()=="serverMessage") {
                                    log.append("<em>"+node.nextSibling().nextSibling().nextSiblingElement().text()+"<\em>");
                                    ui->messageList->append(log);
                                } else if(node.nextSibling().nextSibling().nextSiblingElement().tagName()=="formattedMessage") {
                                    QString message=node.nextSibling().nextSibling().nextSiblingElement().text().mid(node.nextSibling().nextSibling().nextSiblingElement().text().indexOf(")")+1);
                                    QString color=node.nextSibling().nextSibling().nextSiblingElement().text().mid(node.nextSibling().nextSibling().nextSiblingElement().text().indexOf("(")+1, node.nextSibling().nextSibling().nextSiblingElement().text().indexOf(",")-1);
//                                    qDebug()<<"COLOR"<<color;
                                    QString font=node.nextSibling().nextSibling().nextSiblingElement().text().mid(node.nextSibling().nextSibling().nextSiblingElement().text().indexOf(",")+1, node.nextSibling().nextSiblingElement().text().indexOf(")")-2);
//                                    qDebug()<<"FONT"<<font;
                                    QString weight=node.nextSibling().nextSibling().nextSiblingElement().text().mid(node.nextSibling().nextSiblingElement().text().indexOf(")")-2, node.nextSibling().nextSibling().nextSiblingElement().text().indexOf(")"));
//                                    qDebug()<<"WEIGHT"<<weight;
                                    log.append("<font color="+color/*+" font-size="+weight+" font-family="+font+*/+">"+message+"</font>");
                                    ui->messageList->append(log);
                                } else if(node.nextSibling().nextSibling().nextSiblingElement().tagName()=="imageMessage") {
                                    ui->messageList->append(log);
                                    QImage image=QImage::fromData(QByteArray::fromBase64(node.nextSibling().nextSibling().nextSiblingElement().text().toUtf8()), "PNG");
                                    QImage image_new=image.scaled(320,240);
                                    QTextCursor newCursor=ui->messageList->textCursor();
                                    newCursor.movePosition(QTextCursor::End);
                                    ui->messageList->setTextCursor(newCursor);
                                    ui->messageList->textCursor().insertBlock();
                                    ui->messageList->textCursor().insertImage(image_new);
                                } else if(node.nextSibling().nextSibling().nextSiblingElement().tagName()=="fileMessage") {
                                    QString filename;
                                    QString md5;
                                    log.append(node.nextSibling().nextSibling().nextSiblingElement().text());
                                    ui->messageList->append(log);
                                }
                            } else if(tagName=="message") {
//                                qDebug()<<"Message is: "<<element.text();
                            } else if(tagName=="serverMessage") {
//                                qDebug()<<"ServerMessage is: "<<element.text();
                            }
                        }
                        node=node.nextSibling();
                    }
                }
                domNode=domNode.nextSibling();
            }
        }
        file.close();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
