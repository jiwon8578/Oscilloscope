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

private:
    Ui::fftsetup *ui;
};

#endif // FFTSETUP_H
