#ifndef OSCISETUP_H
#define OSCISETUP_H

#include <QWidget>
#include <QCloseEvent>
#include <QString>
#include <QLineEdit>

class freqPlot;

namespace Ui {
class OsciSetup;
}

class OsciSetup : public QWidget
{
    Q_OBJECT

public:
    explicit OsciSetup(QWidget *parent = nullptr);
    ~OsciSetup();
    static double time;
    static double volt;
    static QString timelabel;
    static QString voltlabel;
    static QString timeunitlabel;
    static QString voltunitlabel;
    QString timeunitpush() const;
    QList<QString> setup_save_data();

signals:
    void entered();
//public slots:
//    void textChanged(QString);
private slots:
    //void on_setupButton_clicked();
//    QString timeunitpush() const;

    void on_triggerToZeroBtn_clicked();
    void save_time();
    void save_voltage();
    void save_time_unit();
    void save_voltage_unit();
    void save_coupling();
    void save_probe();
    void save_filter();
    void save_triggerMode();
    void save_triggerSweep();
    void save_triggerSlope();

    void on_ResetToDefBtn_clicked();

private:
    Ui::OsciSetup *ui;
    freqPlot *test;
    void closeEvent(QCloseEvent *event) override;
    QString save_time_var;
    QString save_voltage_var;
    QString unit_time;
    QString unit_volt;
    QString coupling;
    QString probe;
    QString filter;
    QString triggerMode;
    QString triggerSweep;
    QString triggerSlope;

};

#endif // OSCISETUP_H
