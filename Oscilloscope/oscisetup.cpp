#include "oscisetup.h"
#include "ui_oscisetup.h"
#include "mainwindow.h"
#include <QCloseEvent>

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

QString OsciSetup::currentText() const //test
{
    return ui->comboBox->currentText();
}

bool MainWindow::isOsciSetupOpen;

void OsciSetup::closeEvent(QCloseEvent *event)
{
    MainWindow::isOsciSetupOpen = false;
    event->accept();
}
