#include "oscisetup.h"
#include "ui_oscisetup.h"
#include "mainwindow.h"
#include <QCloseEvent>

OsciSetup::OsciSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OsciSetup)
{
    ui->setupUi(this);
    ui->osciSetupLabel->setStyleSheet("font-weight:bold");
    ui->osciSetupLabel->setAlignment(Qt::AlignCenter);
    //connect(ui->setupButton,SIGNAL(clicked()),this,SLOT(pushvalue(double)));

}

OsciSetup::~OsciSetup()
{
    delete ui;
}


bool MainWindow::isOsciSetupOpen;

void OsciSetup::closeEvent(QCloseEvent *event)
{
    MainWindow::isOsciSetupOpen = false;
    event->accept();
}


//double OsciSetup::pushvalue(double x)
//{
//    x = ui->timeEdit->text().toDouble();
//    emit entered(x);
//    //y = ui->voltageEdit->text().toDouble();
//    return x;

//}
