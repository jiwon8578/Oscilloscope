#include "oscisetup.h"
#include "ui_oscisetup.h"
#include "mainwindow.h"
#include "freqplot.h"
#include <QMessageBox>
#include <QMdiSubWindow>
#include <QDebug>

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
    connect(ui->timeEdit, SIGNAL(textChanged(const QString&)), this, SLOT(save_time_unit()));
    connect(ui->voltageEdit, SIGNAL(textChanged(const QString&)), this, SLOT(save_voltage_unit()));
    connect(ui->timeComboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_time_unit()));
    connect(ui->voltageComboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_voltage_unit()));
    connect(ui->couplingComboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_coupling()));
    connect(ui->probeComboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_probe()));
    connect(ui->filterComboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_filter()));
    connect(ui->triggerModeComboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_triggerMode()));
    connect(ui->triggerSweepComboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_triggerSweep()));
    connect(ui->triggerSlopeComboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_triggerSlope()));

    timelabel = save_time_var;
    voltlabel = save_voltage_var;
    timeunitlabel = unit_time;
    voltunitlabel = unit_volt;

    //coupling combobox안에 item추가
    ui->couplingComboBox->addItem("SELECT");
    ui->couplingComboBox->addItem("AC");
    ui->couplingComboBox->addItem("DC");
    ui->couplingComboBox->addItem("GND");

    //probe combobox안에 item추가
    ui->probeComboBox->addItem("SELECT");
    ui->probeComboBox->addItem("x1");
    ui->probeComboBox->addItem("x10");
    ui->probeComboBox->addItem("x100");
    ui->probeComboBox->addItem("x1000");

    //filter combobox안에 item추가
    ui->filterComboBox->addItem("SELECT");
    ui->filterComboBox->addItem("None");
    ui->filterComboBox->addItem("Lower");
    ui->filterComboBox->addItem("Higer");

    //trigger mode combobox안에 item추가
    ui->triggerModeComboBox->addItem("SELECT");
    ui->triggerModeComboBox->addItem("Edge");
    ui->triggerModeComboBox->addItem("Pulse");

    //trigger sweep combobox안에 item추가
    ui->triggerSweepComboBox->addItem("SELECT");
    ui->triggerSweepComboBox->addItem("Auto");
    ui->triggerSweepComboBox->addItem("Normal");
    ui->triggerSweepComboBox->addItem("Single");

    //trigger slope combobox안에 item추가
    ui->triggerSlopeComboBox->addItem("SELECT");
    ui->triggerSlopeComboBox->addItem("+");
    ui->triggerSlopeComboBox->addItem("-");


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
    ui->timeEdit->setText("0");
    ui->voltageEdit->setText("0");
    ui->couplingComboBox->setCurrentIndex(0);
    ui->probeComboBox->setCurrentIndex(0);
    ui->filterComboBox->setCurrentIndex(0);
    ui->triggerModeComboBox->setCurrentIndex(0);
    ui->triggerSweepComboBox->setCurrentIndex(0);
    ui->triggerSlopeComboBox->setCurrentIndex(0);
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
    /*else
    {
        QMessageBox::warning(this,"Select Unit","you must select time-unit");
    }
    */
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
   /* else
    {
        QMessageBox::warning(this,"Select Unit","you must select volt-unit");
    }
    */

}

void OsciSetup::save_coupling() {
    coupling = ui->couplingComboBox->currentText();
}

void OsciSetup::save_probe() {
    probe = ui->probeComboBox->currentText();
}

void OsciSetup::save_filter() {
    filter = ui->filterComboBox->currentText();
}

void OsciSetup::save_triggerMode() {
    triggerMode = ui->triggerModeComboBox->currentText();
}

void OsciSetup::save_triggerSweep() {
    triggerSweep = ui->triggerSweepComboBox->currentText();
}

void OsciSetup::save_triggerSlope() {
    triggerSlope = ui->triggerSlopeComboBox->currentText();
}

QList<QString> OsciSetup::setup_save_data() {
    QList<QString> *save_data_list = new QList<QString>();

    save_data_list->append(save_time_var);
    save_data_list->append(unit_time);
    save_data_list->append(save_voltage_var);
    save_data_list->append(unit_volt);
    save_data_list->append(coupling);
    save_data_list->append(probe);
    save_data_list->append(filter);
    save_data_list->append(triggerMode);
    save_data_list->append(triggerSweep);
    save_data_list->append(triggerSlope);

    return *save_data_list;
}

void OsciSetup::on_ResetToDefBtn_clicked()
{
    ui->timeEdit->setText("400");
    ui->timeComboBox->setCurrentIndex(3);
    ui->voltageEdit->setText("500");
    ui->voltageComboBox->setCurrentIndex(2);
    ui->couplingComboBox->setCurrentIndex(1);
    ui->probeComboBox->setCurrentIndex(1);
    ui->filterComboBox->setCurrentIndex(1);
    ui->triggerModeComboBox->setCurrentIndex(1);
    ui->triggerSweepComboBox->setCurrentIndex(1);
    ui->triggerSlopeComboBox->setCurrentIndex(2);
}
