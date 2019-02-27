#include "testtargetsetupdialog.h"
#include "ui_testtargetsetupdialog.h"

TestTargetSetupDialog::TestTargetSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestTargetSetupDialog)
{
    ui->setupUi(this);
    ui->ttSetupLabel->setStyleSheet("font-weight: bold");
    ui->ttSetupLabel->setAlignment(Qt::AlignCenter);
    resize(150, 300);
}

TestTargetSetupDialog::~TestTargetSetupDialog()
{
    delete ui;
}
