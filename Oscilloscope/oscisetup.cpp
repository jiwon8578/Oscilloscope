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

void OsciSetup::on_setupButton_clicked()
{
    double volt = ui->voltageEdit->text().toDouble();
    double time = ui->timeEdit->text().toDouble();
    emit entered(time, volt);
}
