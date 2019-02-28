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


private slots:
    void inputvalue(double);

private:
    Ui::freqPlot *ui;
    //OsciSetup *sender;
    //void createfreqPlot();

};

#endif // FREQPLOT_H
