#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QVBoxLayout>
#include <QPushButton>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    QVBoxLayout *layout = new QVBoxLayout();

    this->setLayout(layout);
    this->setWindowTitle("About..");
    this->resize(400, 150);

    versionLabel = new QLabel("Version 1.0.1");
    versionLabel->setMaximumWidth(100);

    updateButton = new QPushButton("Update");
    updateButton->setMaximumWidth(100);

    homepageButton = new QPushButton("Homepage");
    homepageButton->setMaximumWidth(100);

    layout->addWidget(versionLabel);
    layout->addWidget(updateButton);
    layout->addWidget(homepageButton);
    layout->setAlignment(versionLabel, Qt::AlignCenter);
    layout->setAlignment(updateButton, Qt::AlignCenter);
    layout->setAlignment(homepageButton, Qt::AlignCenter);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
