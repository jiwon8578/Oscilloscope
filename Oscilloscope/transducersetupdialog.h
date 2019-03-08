#ifndef TRANSDUCERSETUPDIALOG_H
#define TRANSDUCERSETUPDIALOG_H

#include <QDialog>

namespace Ui {
class TransducerSetupDialog;
}

class TransducerSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransducerSetupDialog(QWidget *parent = nullptr);
    ~TransducerSetupDialog();

private slots:
    void on_resetBtn_clicked();

private:
    Ui::TransducerSetupDialog *ui;
};

#endif // TRANSDUCERSETUPDIALOG_H
