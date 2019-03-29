#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMdiSubWindow>
#include "fftplot.h"
#include "freqplot.h"
#include "oscisetup.h"
#include "transducersetupdialog.h"
#include "testtargetsetupdialog.h"
#include "fftsetup.h"
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QComboBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #454548;"); //background 색상 변경
    setCentralWidget(ui->mdiArea);
    ui->menuBar->setStyleSheet("QMenuBar{background-color: rgb(105, 105, 105)}"
                               "QMenuBar::item {margin-right: 3px; margin-left:3px; padding:5px 5px; background:transparent; border-radius:4px;}"
                               "QMenuBar::item:selected {background:#a8a8a8}"
                               "QMenuBar::item:pressed{background:#888888}" "QMenu{color:rgb(255,255,255)}" "QMenuBar{color:rgb(199,200,200)}");
    ui->menuFile->setStyleSheet("QMenu::item:selected{background-color:rgb(30,30,250)}");
    ui->menuView->setStyleSheet("QMenu::item:selected{background-color:rgb(30,30,250)}");
    ui->menuSetup->setStyleSheet("QMenu::item:selected{background-color:rgb(30,30,250)}");
    ui->menuUtility->setStyleSheet("QMenu::item:selected{background-color:rgb(30,30,250)}");
    ui->menuCursor->setStyleSheet("QMenu::item:selected{background-color:rgb(30,30,250)}");
    ui->menuAcquire->setStyleSheet("QMenu::item:selected{background-color:rgb(30,30,250)}");
    ui->menuMeasure->setStyleSheet("QMenu::item:selected{background-color:rgb(30,30,250)}");
    ui->menuHelp->setStyleSheet("QMenu::item:selected{background-color:rgb(30,30,250)}");


    osWaveformWin = ui->mdiArea->addSubWindow(freqPlotObj);
    osWaveformWin->resize(1360, 440);
    osWaveformWin->show();

    osSetupWin = ui->mdiArea->addSubWindow(osciSetupObj);
    osSetupWin->resize(500, 440);
    osSetupWin->show();

    fftWaveformWin = ui->mdiArea->addSubWindow(fftPlotObj);
    fftWaveformWin->resize(1360, 440);
    fftWaveformWin->show();

    fftSetupWin = ui->mdiArea->addSubWindow(fftSetupObj);
    fftSetupWin->resize(500, 440);
    fftSetupWin->show();



    setWindowTitle("Oscilloscope");
    resize(1920, 1080);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSubWindow_plot(QWidget *widget) //mdiArea에 sub window를 띄우는 함수 - plot용
{
    auto window = ui->mdiArea->addSubWindow(widget);
    window->resize(400,400);
    window->show();
}

void MainWindow::loadSubWindow_setup(QWidget *widget) //mdiArea에 sub window를 띄우는 함수 - setup용
{
    auto window = ui->mdiArea->addSubWindow(widget);
    window->resize(400,500);
    window->show();
}

void MainWindow::on_actionOscilloscope_triggered() //view - oscilloscope plot
{
    if(osWaveformWin->isHidden()) {
        osWaveformWin->show();
    } else {
        osWaveformWin->hide();
    }
}


void MainWindow::on_actionOscilloscope_Setup_Window_triggered() //view - oscilloscope setup
{    
    if(osSetupWin->isHidden()) {
        osSetupWin->show();
    } else {
        osSetupWin->hide();
    }
}


void MainWindow::on_actionFFT_Waveform_Window_triggered() //view - fft plot
{
    if(fftWaveformWin->isHidden()) {
        fftWaveformWin->show();
    } else {
      fftWaveformWin->hide();
    }
}

void MainWindow::on_actionFFT_Setup_Window_triggered() //view - fft setup
{
    if(fftSetupWin->isHidden()) {
        fftSetupWin->show();
    } else {
        fftSetupWin->hide();
    }
}

void MainWindow::on_actionOscilloscope_Setup_triggered() //setup - oscilloscope setup
{
    if(osSetupWin->isHidden()) {
        osSetupWin->show();
    }
}

void MainWindow::on_actionArrange_All_Window_triggered() //view - arrange all window
{
    osWaveformWin->move(0, 0);
    if(osWaveformWin->isHidden()) {
        osWaveformWin->show();
    }
    osSetupWin->move(400, 0);
    if(osSetupWin->isHidden()) {
        osSetupWin->show();
    }
    fftWaveformWin->move(800, 0);
    if(fftWaveformWin->isHidden()) {
        fftWaveformWin->show();
    }
    fftSetupWin->move(1200, 0);
    if(fftSetupWin->isHidden()) {
        fftSetupWin->show();
    }
}

void MainWindow::on_actionFull_Screen_triggered() //view - full screen
{
    this->showMaximized();
}

void MainWindow::on_actionNone_triggered()
{
    QCursor none = QCursor(Qt::BlankCursor);
    freqPlotObj->setCursor(none);
}

void MainWindow::on_actionCross_triggered()
{
   QCursor cross = QCursor(Qt::CrossCursor);
   freqPlotObj->setCursor(cross);
}


void MainWindow::on_actionVertical_triggered()
{
    QCursor sizeVer= QCursor(Qt::SizeVerCursor);
    freqPlotObj->setCursor(sizeVer);
}

void MainWindow::on_actionHorizontal_triggered()
{
    QCursor sizeHor = QCursor(Qt::SizeHorCursor);
    freqPlotObj->setCursor(sizeHor);
}

void MainWindow::on_actionArrow_triggered()
{
    QCursor arrow = QCursor(Qt::ArrowCursor);
    freqPlotObj->setCursor(arrow);
}

void MainWindow::on_actionTransducer_Setup_triggered() //utility - transducer setup
{

    transducerSetup = new TransducerSetupDialog(this);
    transducerSetup->show();
}


void MainWindow::on_actionTest_Target_Setup_triggered() //utility - test target setup
{
    testTargetSetup = new TestTargetSetupDialog(this);
    testTargetSetup->show();
}

void MainWindow::on_actionScreen_Capture_triggered() //utility - screen capture
{
    QPixmap pic = this->grab();
    //pic.save("" + QString::number(imageCount) + ".png"); //""안에 경로 입력
    imageCount++;
}

void MainWindow::on_actionDelete_Setup_triggered() //utility - delete setup
{
    transducerSetup->on_resetBtn_clicked();
    testTargetSetup->on_resetBtn_clicked();
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionFFT_Analyzer_triggered() //setup - fft setup
{
    if(fftSetupWin->isHidden()) {
        fftSetupWin->show();
    }
}

void MainWindow::on_actionOpen_File_triggered() //File - Open file
{
    QString filter = "All File (*.*) ;; Csv File (*.csv)";
    filename = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(), filter);
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    //QString content = file.readAll();

    file.close();
}

void MainWindow::on_actionSave_File_triggered() //File - Save File
{
    QString filter = "All File (*.*) ;; Csv File (*.csv)";
    filename = QFileDialog::getSaveFileName(this, "Save File", QDir::homePath(), filter);
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    //QString content = file.readAll();

    file.close();
}


void MainWindow::on_actionLoad_Setup_triggered() //File - Load Setup
{
    QString filter = "All File (*.*) ;; Csv File (*.csv)";
        filename = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(), filter);
        QFile file(filename);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QVector <QString> data;
        QTextStream in(&file);

        while (!in.atEnd()) {
             QString line = in.readLine();// read first line and so on
             QStringList fields = line.split(',');// split the string
             data.append(fields.at(0));
        }

        QList<QLineEdit*> blanks_le = this->findChildren<QLineEdit*>();
        QList<QComboBox*> blanks_cb = this->findChildren<QComboBox*>();

        int index = 0;
        blanks_le[2]->setText(data[0]);

        if(data[1] == "s") {
            index = 1;
        } else if(data[1] == "ms") {
            index = 2;
        } else if(data[1] == "μs") {
            index = 3;
        } else {
            index = 4;
        }
        blanks_cb[6]->setCurrentIndex(index); //freq time unit

        blanks_le[3]->setText(data[2]);

        if(data[3] == "v") {
            index = 1;
        } else {
            index = 2;
        }
        blanks_cb[7]->setCurrentIndex(index); //freq voltage unit

        if(data[4] == "AC") {
            index = 1;
        } else if(data[4] == "DC"){
            index = 2;
        } else {
            index = 3;
        }
        blanks_cb[0]->setCurrentIndex(index);

        if(data[5] == "x1") {
            index = 1;
        } else if(data[5] == "x10"){
            index = 2;
        } else if(data[5] == "x100"){
            index = 3;
        } else {
            index = 4;
        }
        blanks_cb[1]->setCurrentIndex(index);

        if(data[6] == "None") {
            index = 1;
        } else if(data[6] == "Lower"){
            index = 2;
        } else {
            index = 3;
        }
        blanks_cb[2]->setCurrentIndex(index);

        if(data[7] == "Edge") {
            index  = 1;
        } else {
            index = 2;
        }
        blanks_cb[3]->setCurrentIndex(index);

        if(data[8] == "Auto") {
            index = 1;
        } else if(data[8] == "Normal"){
            index = 2;
        } else {
            index = 3;
        }
        blanks_cb[4]->setCurrentIndex(index);

        if(data[9] == "+") {
            index  = 1;
        } else {
            index = 2;
        }
        blanks_cb[5]->setCurrentIndex(index);

        //여기서부터 fftsetup
        blanks_le[4]->setText(data[10]);

        if(data[11] == "256") {
            index = 1;
        } else if(data[11] == "512") {
            index = 2;
        } else if(data[11] == "1024") {
            index = 3;
        } else if(data[11] == "2048") {
            index = 4;
        } else {
            index = 5;
        }
        blanks_cb[8]->setCurrentIndex(index);

        if(data[12] == "Linear") {
            index = 1;
        } else {
            index = 2;
        }
        blanks_cb[9]->setCurrentIndex(index);

        blanks_le[5]->setText(data[13]);

        if(data[14] == "x1") {
            index = 1;
        } else if(data[14] == "x2"){
            index = 2;
        } else if(data[14] == "x4") {
            index = 3;
        } else if(data[14] == "x8") {
            index = 4;
        } else {
            index = 5;
        }
        blanks_cb[10]->setCurrentIndex(index);

        if(data[15] == "ms") {
            index = 1;
        } else if(data[15] == "us") {
            index = 2;
        } else {
            index = 3;
        }
        blanks_cb[11]->setCurrentIndex(index); //fft delay time

        if(data[16] == "V") {
            index = 1;
        } else {
            index = 2;
        }
        blanks_cb[12]->setCurrentIndex(index); //fft vertical time

        blanks_le[0]->setText(blanks_le[2]->text());
        blanks_le[1]->setText(blanks_le[3]->text());


        file.close();

}

void MainWindow::on_actionSave_Setup_triggered()    //File - Save Setup
{
    QList<QString> *save_data_list = new QList<QString>();
       QList<QString> *fft_save_data_list = new QList<QString>();

       *save_data_list = osciSetupObj->setup_save_data();
       *fft_save_data_list = fftSetupObj->fftsetup_save_data();

        QString filter = "Csv File (*.csv)";
        QString filename_save = QFileDialog::getSaveFileName(this, "Save File", QDir::currentPath(), filter);
        QFile file(filename_save);
        if(file.open(QFile::WriteOnly|QFile::Truncate)) {
            QTextStream output(&file);
            for(int i = 0; i < save_data_list->size(); i++) {
                output << save_data_list->at(i) << "\n";
            }
            for(int j = 0; j < fft_save_data_list->size(); j++) {
                output << fft_save_data_list->at(j) << "\n";
            }
        }
        file.close();


}

