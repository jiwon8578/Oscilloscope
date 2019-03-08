#include "fftsetup.h"
#include "ui_fftsetup.h"
#include "mainwindow.h"
#include <QMdiSubWindow>

fftsetup::fftsetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fftsetup)
{
    ui->setupUi(this);
    ui->delaytimecombobox->addItem("SELECT");
    ui->delaytimecombobox->addItem("ms");
    ui->delaytimecombobox->addItem("us");
    ui->delaytimecombobox->addItem("ns");

    ui->nooffreqbinxcombobox->addItem("SELECT");
    ui->nooffreqbinxcombobox->addItem("256");
    ui->nooffreqbinxcombobox->addItem("512");
    ui->nooffreqbinxcombobox->addItem("1024");
    ui->nooffreqbinxcombobox->addItem("2048");
    ui->nooffreqbinxcombobox->addItem("4096");

    ui->scalecombobox->addItem("SELECT");
    ui->scalecombobox->addItem("Linear");
    ui->scalecombobox->addItem("dB");

    ui->verticaldivcombobox->addItem("SELECT");
    ui->verticaldivcombobox->addItem("V");
    ui->verticaldivcombobox->addItem("mV");

    ui->horizontalcombobox->addItem("SELECT");
    ui->horizontalcombobox->addItem("x1");
    ui->horizontalcombobox->addItem("x2");
    ui->horizontalcombobox->addItem("x4");
    ui->horizontalcombobox->addItem("x8");
    ui->horizontalcombobox->addItem("x16");

}

fftsetup::~fftsetup()
{
    delete ui;
}

QMdiSubWindow *MainWindow::fftSetupWin;

void fftsetup::closeEvent(QCloseEvent *event)
{
    MainWindow::fftSetupWin->hide();
    event->ignore();
}

