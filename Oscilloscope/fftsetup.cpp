#include "fftsetup.h"
#include "ui_fftsetup.h"
#include "mainwindow.h"
#include <QMdiSubWindow>
#include <QMessageBox>
#include "fftplot.h"

double fftsetup::time_fft;
double fftsetup::volt_fft;
QString fftsetup::timelabel_fft;
QString fftsetup::timeunitlabel_fft;
QString fftsetup::voltlabel_fft;
QString fftsetup::voltunitlabel_fft;

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

QString fftsetup::delaytimetext() const
{
    return ui->delaytimecombobox->currentText();
}

QString fftsetup::nooffreqxtext() const
{
    return ui->nooffreqbinxcombobox->currentText();
}

QString fftsetup::scaletext() const
{
    return  ui->scalecombobox->currentText();
}

QString fftsetup::verticaltext() const
{
    return ui->verticaldivcombobox->currentText();
}

QString fftsetup::horizontaltext() const
{
    return ui->horizontalcombobox->currentText();
}


QMdiSubWindow *MainWindow::fftSetupWin;

void fftsetup::closeEvent(QCloseEvent *event)
{
    MainWindow::fftSetupWin->hide();
    event->ignore();
}


void fftsetup::on_pushButton_clicked()
{
    QString t = ui->delaytimelineedit->text();
    QString v = ui->verticaldivlineedit->text();
    QString unit_time = ui->delaytimecombobox->currentText();
    QString unit_volt = ui->verticaldivcombobox->currentText();
    timelabel_fft = ui->delaytimelineedit->text();
    voltlabel_fft = ui->verticaldivlineedit->text();
    timeunitlabel_fft = ui->delaytimecombobox->currentText();
    voltunitlabel_fft = ui->verticaldivcombobox->currentText();
    // switch문 써야되낭
    if(unit_time=="ms")
    {
        time_fft = t.toDouble()*(10^-2);
    }
    else if(unit_time=="us")
    {
        time_fft = t.toDouble()*(10^-6);
    }
    else if(unit_time=="ns")
    {
        time_fft = t.toDouble()*(10^-9);
    }
    else
    {
        QMessageBox::warning(this,"Select Unit","you must select time-unit");
    }

    if(unit_volt=="V")
    {
        volt_fft = v.toDouble();
    }
    else if(unit_volt=="mV")
    {
        volt_fft = v.toDouble()*(10^-2);
    }
    else
    {
        QMessageBox::warning(this,"Select Unit","you must select volt-unit");
    }

}
