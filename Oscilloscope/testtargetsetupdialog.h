#ifndef TESTTARGETSETUPDIALOG_H
#define TESTTARGETSETUPDIALOG_H

#include <QDialog>

namespace Ui {
class TestTargetSetupDialog;
}

class TestTargetSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestTargetSetupDialog(QWidget *parent = nullptr);
    ~TestTargetSetupDialog();

public slots:
    void on_resetBtn_clicked();

private slots:


private:
    Ui::TestTargetSetupDialog *ui;
};

#endif // TESTTARGETSETUPDIALOG_H
