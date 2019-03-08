#include "transducersetupdialog.h"
#include "ui_transducersetupdialog.h"

TransducerSetupDialog::TransducerSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransducerSetupDialog)
{
    ui->setupUi(this);
    ui->transducerSetupLabel->setStyleSheet("font-weight: bold");
    ui->transducerSetupLabel->setAlignment(Qt::AlignCenter);
    resize(150, 300);
}

TransducerSetupDialog::~TransducerSetupDialog()
{
    delete ui;
}

void TransducerSetupDialog::on_resetBtn_clicked()
{
    foreach(QLineEdit *lineEdit, this->findChildren<QLineEdit*>()) {
        lineEdit->clear();
    }
}


