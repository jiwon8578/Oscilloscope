#include "oscisetup.h"
#include "ui_oscisetup.h"
#include "mainwindow.h"
#include "freqplot.h"
#include <QMessageBox>
#include <QMdiSubWindow>

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

    QString t = ui->timeEdit->text();
    QString v = ui->voltageEdit->text();

    connect(ui->timeEdit, SIGNAL(textChanged(const QString&)), this, SLOT(save_time()));
    connect(ui->voltageEdit, SIGNAL(textChanged(const QString&)), this, SLOT(save_voltage()));
    connect(ui->timeComboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_time_unit()));
    connect(ui->voltageComboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_voltage_unit()));

    timelabel = save_time_var;
    voltlabel = save_voltage_var;
    timeunitlabel = unit_time;
    voltunitlabel = unit_volt;
}

OsciSetup::~OsciSetup()
{
    delete ui;
}


//QString OsciSetup::timeunitpush() const
//{
//    return ui->timeComboBox->currentText();

//}


QMdiSubWindow *MainWindow::osSetupWin;

void OsciSetup::closeEvent(QCloseEvent *event)
{
    MainWindow::osSetupWin->hide();
    event->ignore();
}

void OsciSetup::on_triggerToZeroBtn_clicked()
{
    ui->timeEdit->setText("");
    ui->voltageEdit->setText("");
}

void OsciSetup::save_time() {
    save_time_var = ui->timeEdit->text();
}

void OsciSetup::save_voltage() {
    save_voltage_var = ui->voltageEdit->text();
}

void OsciSetup::save_time_unit() {
    unit_time = ui->timeComboBox->currentText();

    if(unit_time=="s")
    {
        time = save_time_var.toDouble();
    }
    else if(unit_time=="ms")
    {
        time = save_time_var.toDouble()*(10^-2);}
    else if(unit_time=="μs")
    {
        time = save_time_var.toDouble()*(10^-6);
    }
    else if(unit_time=="nm")
    {
        time = save_time_var.toDouble()*(10^-9);
    }
    else
    {
        QMessageBox::warning(this,"Select Unit","you must select time-unit");
    }
}

void OsciSetup::save_voltage_unit() {
    unit_volt = ui->voltageComboBox->currentText();

    if(unit_volt=="v")
    {
        volt = save_voltage_var.toDouble();
    }
    else if(unit_volt=="mv")
    {
        volt = save_voltage_var.toDouble()*(10^-2);
    }
    else
    {
        QMessageBox::warning(this,"Select Unit","you must select volt-unit");
    }

}
