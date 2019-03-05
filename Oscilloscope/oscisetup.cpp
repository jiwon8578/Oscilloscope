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
    ui->timeComboBox->addItem("SELECT");
    ui->timeComboBox->addItem("s");
    ui->timeComboBox->addItem("ms");
    ui->timeComboBox->addItem("μs");
    ui->timeComboBox->addItem("nm");
    ui->voltageComboBox->addItem("SELECT");
    ui->voltageComboBox->addItem("v");
    ui->voltageComboBox->addItem("mv");
//    test = new freqPlot;
//    connect(ui->timeEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
//    connect(ui->setupButton,SIGNAL(clicked()),this,OsciSetup::timeunitpush());
}

OsciSetup::~OsciSetup()
{
    delete ui;
}


//QString OsciSetup::timeunitpush() const
//{
//    return ui->timeComboBox->currentText();

//}


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
    QString unit_time = ui->timeComboBox->currentText();
    QString unit_volt = ui->voltageComboBox->currentText();
    timelabel = ui->timeEdit->text();
    voltlabel = ui->voltageEdit->text();
    timeunitlabel = ui->timeComboBox->currentText();
    voltunitlabel = ui->voltageComboBox->currentText();
    // switch문 써야되낭
    if(unit_time=="s")
    {
        time = t.toDouble();
    }
    else if(unit_time=="ms")
    {
        time = t.toDouble()*(10^-2);}
    else if(unit_time=="μs")
    {
        time = t.toDouble()*(10^-6);
    }
    else if(unit_time=="nm")
    {
        time = t.toDouble()*(10^-9);
    }
    else
    {
        QMessageBox::warning(this,"Select Unit","you must select time-unit");
    }

    if(unit_volt=="v")
    {
        volt = v.toDouble();
    }
    else if(unit_volt=="mv")
    {
        volt = v.toDouble()*(10^-2);
    }
    else
    {
        QMessageBox::warning(this,"Select Unit","you must select volt-unit");
    }


}


void OsciSetup::on_triggerToZeroBtn_clicked()
{
    ui->timeEdit->setText("");
    ui->voltageEdit->setText("");
}
