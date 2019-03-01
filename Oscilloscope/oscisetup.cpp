#include "oscisetup.h"
#include "ui_oscisetup.h"
#include "mainwindow.h"
#include "freqplot.h"
#include <QCloseEvent>
#include <QMessageBox>
OsciSetup::OsciSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OsciSetup)
{
    ui->setupUi(this);
    ui->osciSetupLabel->setStyleSheet("font-weight:bold");
    ui->osciSetupLabel->setAlignment(Qt::AlignCenter);
    ui->timeComboBox->addItem("s");
    ui->timeComboBox->addItem("ms");
    ui->timeComboBox->addItem("μs");
    ui->timeComboBox->addItem("nm");
    ui->voltageComboBox->addItem("v");
    ui->voltageComboBox->addItem("mv");
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
    QString t = ui->timeEdit->text();
    QString v = ui->voltageEdit->text();
    if(t=="s")
    {
        time = t.toDouble();
    }
    else if(t=="ms")
    {
        time = t.toDouble()*(10^-2);
    }
    else if(t=="μs")
    {
        time = t.toDouble()*(10^-6);
    }
    else
    {
        time = t.toDouble()*(10^-9);
    }

    if(v=="v")
    {
        volt = v.toDouble();
    }
    else
    {
        volt = v.toDouble()*(10^-2);
    }
}
