#include "fftsetup.h"
#include "ui_fftsetup.h"

fftsetup::fftsetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fftsetup)
{
    ui->setupUi(this);
}

fftsetup::~fftsetup()
{
    delete ui;
}

