#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTime>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <string>
#include <iostream>
#include <time.h>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cstdio>
#include <QProgressBar>
#include <QDebug>
#include <hsi2l.h>
#include <opencv2/opencv.hpp>
#include <mlabel.h>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>

using namespace std;
//using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    public slots:
        void Mouse_pos();
        void Img_pos();



private slots:
    void on_ReadHSI_button_clicked();

    void on_changeBand_ScrollBar_sliderMoved(int position);

    void on_imgThreshold_ScrollBar_sliderMoved(int position);

    void on_changeROI_ScrollBar_sliderMoved(int position);

    void on_selectSpectral_Button_clicked();

    void on_saveSpecdata_button_clicked();

    void on_get100PixDta_Button_clicked();

    void on_SaveJPG_Button_clicked();

private:
    Ui::MainWindow *ui;
public:

    void loadRawData(hsi2l &seeHSI);
    void readHyperspectralData(hsi2l &seeHSI);
    void GetPositionSpectral(int u,int v,int i); //-- 滑鼠事件: 獲取spectral
    void SavePositionSpectralData();
    void Save121PositionSpectralData();

    std::string pathFold;
    QString iniHDRpath;
    cv::Mat imageHSI;
    cv::Mat mouseRect;
    cv::Mat backupimageHSI;
    hsi2l myHSI;
    WeiChang2L mytool;
    QChartView *chartView = new QChartView(chart);
    QChart *chart = new QChart();
    QLineSeries *stupid = new QLineSeries();
    QMainWindow window;


};

#endif // MAINWINDOW_H
