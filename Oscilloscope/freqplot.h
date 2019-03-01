#ifndef FREQPLOT_H
#define FREQPLOT_H

#include <QWidget>
#include "oscisetup.h" //test

class OsciSetup; //test

namespace Ui {
class freqPlot;
}

class freqPlot : public QWidget
{
    Q_OBJECT

public:
    explicit freqPlot(QWidget *parent = nullptr);
   // OsciSetup *sender;
    ~freqPlot();
    double t;
    double v;

private slots:
    //void inputvalue(double);

    void on_pushButton_clicked();

private:
    Ui::freqPlot *ui;
    //OsciSetup *sender;

};

#endif // FREQPLOT_H
