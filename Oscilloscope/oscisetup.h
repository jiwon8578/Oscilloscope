#ifndef OSCISETUP_H
#define OSCISETUP_H

#include <QWidget>
#include <QCloseEvent>
#include <QString>

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



//public slots:
//    QString pushtime() const;
//    QString pushvolt() const;

//signals:
//    void timeEntered(double);

private slots:
    void on_setupButton_clicked();

private:
    Ui::OsciSetup *ui;
    freqPlot *test;
    void closeEvent(QCloseEvent *event) override;
};

#endif // OSCISETUP_H
