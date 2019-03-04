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
    QString timepush() const;
    QString timeunitpush() const;

public slots:
    void textChanged(QString);
private slots:
    void on_setupButton_clicked();

private:
    Ui::OsciSetup *ui;
    freqPlot *test;
    void closeEvent(QCloseEvent *event) override;

};

#endif // OSCISETUP_H
