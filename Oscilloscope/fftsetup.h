#ifndef FFTSETUP_H
#define FFTSETUP_H

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QCloseEvent>

class fftplot;

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

    static double time_fft;
    static double volt_fft;
    static QString timelabel_fft;
    static QString voltlabel_fft;
    static QString timeunitlabel_fft;
    static QString voltunitlabel_fft;

private slots:

    //void on_pushButton_clicked();
    void save_time();
    void save_voltage();
    void save_time_unit();
    void save_voltage_unit();

private:
    Ui::fftsetup *ui;
    void closeEvent(QCloseEvent *event) override;
    QString save_time_var;
    QString save_voltage_var;
    QString unit_time;
    QString unit_volt;
};

#endif // FFTSETUP_H
