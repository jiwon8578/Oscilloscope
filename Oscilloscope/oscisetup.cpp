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
    //connect(ui->setupButton,SIGNAL(clicked()),this,SLOT(pushvolt()));
    test = new freqPlot;
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


//QString OsciSetup::pushtime() const
//{
//    return ui->timeEdit->text();
//}

//QString OsciSetup::pushvolt() const
//{
//    return ui->comboBox->currentText();
//}

void OsciSetup::on_setupButton_clicked()
{
    test->t = ui->timeEdit->text().toDouble();
    test->v = ui->voltageEdit->text().toDouble();
    QMessageBox::about(this,"result","please");

}
