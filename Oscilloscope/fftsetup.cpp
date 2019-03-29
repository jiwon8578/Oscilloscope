#include "fftsetup.h"
#include "ui_fftsetup.h"
#include "mainwindow.h"
#include <QMdiSubWindow>
#include <QMessageBox>
#include "fftplot.h"

double fftsetup::time_fft;
double fftsetup::volt_fft;
QString fftsetup::timelabel_fft;
QString fftsetup::voltlabel_fft;
QString fftsetup::timeunitlabel_fft;
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

    connect(ui->delaytimelineedit, SIGNAL(textChanged(const QString&)), this, SLOT(save_time()));
    connect(ui->verticaldivlineedit, SIGNAL(textChanged(const QString&)), this, SLOT(save_voltage()));
    connect(ui->delaytimecombobox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_time_unit()));
    connect(ui->verticaldivcombobox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_voltage_unit()));
    connect(ui->nooffreqbinxcombobox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_freqBins()));
    connect(ui->scalecombobox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_scale()));
    connect(ui->horizontalcombobox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(save_horizontal()));

    timelabel_fft = save_time_var;
    voltlabel_fft = save_voltage_var;
    timeunitlabel_fft = unit_time;
    voltunitlabel_fft = unit_volt;

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

void fftsetup::save_time()
{
        save_time_var = ui->delaytimelineedit->text();
}

void fftsetup::save_voltage()
{
        save_voltage_var = ui->verticaldivlineedit->text();
}

void fftsetup::save_time_unit()
{
    unit_time = ui->delaytimecombobox->currentText();

    if(unit_time=="ms")
    {
        time_fft = save_time_var.toDouble()*(10^-2);}
    else if(unit_time=="us")
    {
        time_fft = save_time_var.toDouble()*(10^-6);
    }
    else if(unit_time=="ns")
    {
        time_fft = save_time_var.toDouble()*(10^-9);
    }
    else
    {
        QMessageBox::warning(this,"Select Unit","you must select time-unit");
    }
}

void fftsetup::save_voltage_unit()
{
    unit_volt = ui->verticaldivcombobox->currentText();

    if(unit_volt=="V")
    {
        volt_fft = save_voltage_var.toDouble();
    }
    else if(unit_volt=="mV")
    {
        volt_fft = save_voltage_var.toDouble()*(10^-2);
    }
    else
    {
        QMessageBox::warning(this,"Select Unit","you must select volt-unit");
    }
}

void fftsetup::save_freqBins() {
    freqBins = ui->nooffreqbinxcombobox->currentText();
}

void fftsetup::save_scale() {
    scale = ui->scalecombobox->currentText();
}

void fftsetup::save_horizontal() {
    horizontal = ui->horizontalcombobox->currentText();
}

QList<QString> fftsetup::fftsetup_save_data() {
    QList<QString> *fft_save_data_list = new QList<QString>();

    fft_save_data_list->append(save_time_var);
    fft_save_data_list->append(freqBins);
    fft_save_data_list->append(scale);
    fft_save_data_list->append(save_voltage_var);
    fft_save_data_list->append(horizontal);
    fft_save_data_list->append(unit_time);
    fft_save_data_list->append(unit_volt);

    return *fft_save_data_list;
}
