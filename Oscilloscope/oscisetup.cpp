#include "oscisetup.h"
#include "ui_oscisetup.h"

OsciSetup::OsciSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OsciSetup)
{
    ui->setupUi(this);
    ui->osciSetupLabel->setStyleSheet("font-weight:bold");
    ui->osciSetupLabel->setAlignment(Qt::AlignCenter);
}

OsciSetup::~OsciSetup()
{
    delete ui;
}
