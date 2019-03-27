#ifndef FFTSETUP_H
#define FFTSETUP_H

#include <QWidget>

namespace Ui {
class fftsetup;
}

class fftsetup : public QWidget
{
    Q_OBJECT

public:
    explicit fftsetup(QWidget *parent = nullptr);
    ~fftsetup();

    QString delaytimetext() const;
    QString nooffreqxtext() const;
    QString scaletext() const;
    QString verticaltext() const;
    QString horizontaltext() const;
    static double time;
    static double volt;
    static QString timelabel;
    static QString voltlabel;
    static QString timeunitlabel;
    static QString voltunitlabel;

private slots:

    void on_pushButton_clicked();

private:
    Ui::fftsetup *ui;
    void closeEvent(QCloseEvent *event) override;
};

#endif // FFTSETUP_H
