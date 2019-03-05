#include "fftsetup.h"
#include "ui_fftsetup.h"

fftsetup::fftsetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fftsetup)
{
    ui->setupUi(this);
    resize(300, 420);
}

fftsetup::~fftsetup()
{
    delete ui;
}

