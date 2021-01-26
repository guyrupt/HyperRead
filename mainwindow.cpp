#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::showMaximized();
    ui->StatProgress->setValue(0);
    ui->imgThreshold_ScrollBar->setRange(0,777);
    ui->imgThreshold_ScrollBar->setValue(210); ui->label_2->setNum(ui->imgThreshold_ScrollBar->value());
    ui->changeROI_ScrollBar->setRange(0,100);
    connect(ui->showHSI_label, SIGNAL(mouse_pos()),
            this,  SLOT(Mouse_pos()));//--滑鼠移動--顯示RGB image 的label
    connect(ui->showHSI_label, SIGNAL(mouse_press()),
            this,  SLOT(Img_pos()));


}


MainWindow::~MainWindow()
{
    myHSI.releaseDataHSI();
    delete ui;
}

void MainWindow::Mouse_pos()
{

    ui->label_position->setText(QString("X = %1, Y= %2").arg(ui->showHSI_label->x).arg(ui->showHSI_label->y));
    int rangeROI = ui->changeROI_ScrollBar->value();
    int u = ui->showHSI_label->x; int v= ui->showHSI_label->y;
    mouseRect.create(cv::Size(imageHSI.cols,imageHSI.rows),CV_8UC3);
    mouseRect.setTo(cv::Scalar::all(0)) ;//--背景設為全黑
    imageHSI.copyTo(mouseRect);
    cv::line(mouseRect,cv::Point(u-7,v),cv::Point(u-rangeROI,v),CV_RGB(0,255,0),1,1);//-- 畫+字號
    cv::line(mouseRect,cv::Point(u+rangeROI,v),cv::Point(u+7,v),CV_RGB(0,255,0),1,1);//-- 畫+字號
    cv::line(mouseRect,cv::Point(u,v-7),cv::Point(u,v-rangeROI),CV_RGB(0,255,0),1,1);//-- 畫+字號
    cv::line(mouseRect,cv::Point(u,v+rangeROI),cv::Point(u,v+7),CV_RGB(0,255,0),1,1);
    if(rangeROI != 0){
        cv::rectangle(mouseRect,cv::Point(u-rangeROI,v-rangeROI),cv::Point(u+rangeROI,v+rangeROI),cv::Scalar(0,255,0),1);
    }
    ui->showHSI_label->setPixmap(QPixmap::fromImage(QImage(mouseRect.data
                                                                   ,mouseRect.cols,mouseRect.rows,QImage::Format_RGB888)));
}

void MainWindow::Img_pos()
{
    if(myHSI.selectPointNum==0){
        backupimageHSI.create(cv::Size(imageHSI.cols,imageHSI.rows),CV_8UC3);
        backupimageHSI.setTo(cv::Scalar::all(0));
    }
    myHSI.selectPointNum++;
    QString stats;
    if(ui->checkBox_sick->isChecked()){
        myHSI.status.push_back(0);
        stats="sick";
    }
    else{
        myHSI.status.push_back(1);
        stats="healthy";
    }
    int rangeROI = ui->changeROI_ScrollBar->value();
    string pointCount = std::to_string(myHSI.selectPointNum);
    ui->img_posLbl->setText(QString("X = %1, Y= %2").arg(ui->showHSI_label->img_x).arg(ui->showHSI_label->img_y));
    ui->selectNum_textBrowser->append(QString("%1. %2(%3 , %4)").arg(myHSI.selectPointNum).arg(stats).arg(ui->showHSI_label->img_x).arg(ui->showHSI_label->img_y));
    myHSI.x_selectPoints.push_back(ui->showHSI_label->img_x);
    myHSI.y_selectPoints.push_back(ui->showHSI_label->img_y);
    if(rangeROI != 0){
        cv::rectangle(imageHSI,cv::Point(ui->showHSI_label->img_x-rangeROI,ui->showHSI_label->img_y-rangeROI),cv::Point(ui->showHSI_label->img_x+rangeROI,ui->showHSI_label->img_y+rangeROI),cv::Scalar(0,255,0),1);
        cv::putText(imageHSI,pointCount,
                    cv::Point(ui->showHSI_label->img_x-rangeROI,ui->showHSI_label->img_y+rangeROI+3),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(0,255,0));
        imageHSI.copyTo(backupimageHSI);
    }
    else{
        cv::rectangle(imageHSI,cv::Point(ui->showHSI_label->img_x+1,ui->showHSI_label->img_y+1),cv::Point(ui->showHSI_label->img_x-1,ui->showHSI_label->img_y-1),cv::Scalar(0,255,0),-1);
        cv::putText(imageHSI,pointCount,
                    cv::Point(ui->showHSI_label->img_x,ui->showHSI_label->img_y+3),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(0,255,0));
        imageHSI.copyTo(backupimageHSI);
    }

}

void MainWindow::on_ReadHSI_button_clicked()
{
    QString hdrName;

    if(iniHDRpath==""){
        hdrName = QFileDialog::getOpenFileName(this,tr("Open HDR File"), QString::fromStdString(pathFold), tr("HDR(*.hdr)"));
    }
    else {
        hdrName = QFileDialog::getOpenFileName(this,tr("Open HDR File"), iniHDRpath, tr("HDR(*.hdr)"));
    }
    if (hdrName == nullptr) {
        QMessageBox::information(nullptr, "Error!", "Need HDR file!");
        return;
    }
    myHSI.releaseDataHSI();
    myHSI.initHSI2l(); //--初始化
    QString hdrName_origi = hdrName;
    iniHDRpath = hdrName; //-- To save that user select HDR path
    ui->statusBar->showMessage(hdrName_origi); //-- show HDR path
    hdrName=hdrName.toLocal8Bit();//--使程式可以讀取中文路徑
    myHSI.pathHDR=hdrName.toStdString();

    int len_path=hdrName.length();
    QString filename;
    filename=hdrName.remove(len_path-4,4);//--".hdr"共4個
    myHSI.pathHSI=filename.toStdString();

    QDir qy(filename);
    myHSI._FileName = qy.dirName().toStdString();//--不包含副檔名
    //--包含斜線"/"
    myHSI._FilePath = filename.remove(filename.length()-qy.dirName().length(),qy.dirName().length()).toStdString();
    qDebug() << "Name:" << QString::fromStdString(myHSI._FileName);
    qDebug() << "Path:" << QString::fromStdString(myHSI._FilePath);

    //-----------------------------//
    //--    讀取HDR檔案的資訊      --//
    std::ifstream in(myHSI.pathHDR.c_str(),ios::in);

    std::string linetemp;//--用來比較字串
    char data[40];
    while (!in.eof()) {
        in>>data;
        linetemp=data;
        if(linetemp=="samples"){
            in >> data >> myHSI.samples;//--該行的整數放到samples
            qDebug()<<myHSI.samples;
        }
        if(linetemp=="lines"){
            //-- 解說: 如果檔案太大，則使用原始的myHSI.lines
            //-- 如果檔案不會太大，則是將檔案的lines覆蓋到myHSI.lines
            //-- 在本程式的處理中，以myHSI.lines的資訊為主
            in >> data >>myHSI.lines_original;
            if(1/*myHSI.lines_original < myHSI.lines*/){
                myHSI.lines = myHSI.lines_original;
            }
            qDebug()<<myHSI.lines;
        }
        if(linetemp=="bands"){
            in >> data >> myHSI.bands;
            //string ll2;ll2=data;
            qDebug()<<myHSI.bands;//-- 應該為"="
            ui->changeBand_ScrollBar->setRange(1,myHSI.bands);
//            ui->changeBand_ScrollBar->setVisible(true);
//            ui->band_label->setVisible(true);
        }
        if(linetemp=="wavelength"){
            in >> data >> data >> data;//--"units" "=" "nm"
            in >> data >> data>> data; //--"wavelength" "=" "{"
            float tempF;
            char doCH[10];
            for(int i=0;i<myHSI.bands;++i){
              in >> tempF >> doCH;
              myHSI.spectralIndex.push_back(tempF);
              //qDebug()<<tempF;
            }
        }

    }//--END while
    in.close();
    imageHSI.create(cv::Size(myHSI.samples,myHSI.lines),CV_8UC3);
    imageHSI.setTo(cv::Scalar::all(0)) ;
    loadRawData(myHSI);
    for(int y=0;y<imageHSI.rows;++y){
        for(int x=0;x<imageHSI.cols;++x){
            int val= myHSI.rawDataHSI[y][myHSI.bandCurrent][x]*210/*ui->imgThreshold_ScrollBar->value()*/;//--Line Band Sample

            if(val>255)
                val=255;
            if(val<0)
                val=0;

            imageHSI.ptr<uchar>(y)[x*3]=val;
            imageHSI.ptr<uchar>(y)[x*3+1]=val;
            imageHSI.ptr<uchar>(y)[x*3+2]=val;

        }
    }
    ui->changeBand_ScrollBar->setMaximum(myHSI.bands);
    ui->showHSI_label->setFixedSize(imageHSI.cols,imageHSI.rows);
    ui->showHSI_label->setPixmap(QPixmap::fromImage(QImage(imageHSI.data
                                                                   ,imageHSI.cols,imageHSI.rows,QImage::Format_RGB888)));


}

void MainWindow::on_changeBand_ScrollBar_sliderMoved(int position)
{
    ui->band_label->setText(QString("Band:%1").arg(position));
    imageHSI.setTo(cv::Scalar::all(0)) ;
    for(int y=0;y<imageHSI.rows;++y){
        for(int x=0;x<imageHSI.cols;++x){
            int val= myHSI.rawDataHSI[y][position-1][x] *ui->imgThreshold_ScrollBar->value();//--Line Band Sample

            if(val>255)
                val=255;
            if(val<0)
                val=0;

            imageHSI.ptr<uchar>(y)[x*3]=val;
            imageHSI.ptr<uchar>(y)[x*3+1]=val;
            imageHSI.ptr<uchar>(y)[x*3+2]=val;

        }
    }
    ui->showHSI_label->setPixmap(QPixmap::fromImage(QImage(imageHSI.data
                                                                   ,imageHSI.cols,imageHSI.rows,QImage::Format_RGB888)));

    ui->specIndex_label->
            setText(QString::fromStdString(myHSI.float2str(myHSI.spectralIndex[position-1])).append("nm"));
}

void MainWindow::on_imgThreshold_ScrollBar_sliderMoved(int position)
{
    ui->label_2->setNum(ui->imgThreshold_ScrollBar->value());
    imageHSI.setTo(cv::Scalar::all(0)) ;
    for(int y=0;y<imageHSI.rows;++y){
        for(int x=0;x<imageHSI.cols;++x){
            int val= myHSI.rawDataHSI[y][ui->changeBand_ScrollBar->value()-1][x] *position;//--Line Band Sample

            if(val>255)
                val=255;
            if(val<0)
                val=0;

            imageHSI.ptr<uchar>(y)[x*3]=val;
            imageHSI.ptr<uchar>(y)[x*3+1]=val;
            imageHSI.ptr<uchar>(y)[x*3+2]=val;

        }
    }
    ui->showHSI_label->setPixmap(QPixmap::fromImage(QImage(imageHSI.data
                                                                   ,imageHSI.cols,imageHSI.rows,QImage::Format_RGB888)));

}


void MainWindow::on_changeROI_ScrollBar_sliderMoved(int position)
{
    ui->ROI_label->setNum(position*2+1);
}

void MainWindow::on_selectSpectral_Button_clicked()
{

    for(int i = 0;i<(int)myHSI.x_selectPoints.size();i++){
        GetPositionSpectral(myHSI.x_selectPoints[i],myHSI.y_selectPoints[i],i);
    }
//    GetPositionSpectral(myHSI.x_selectPoints[0],myHSI.y_selectPoints[0]);
//    GetPositionSpectral(myHSI.x_selectPoints[1],myHSI.y_selectPoints[1]);
    qDebug()<<myHSI.selectPointNum;
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();
}

void MainWindow::on_saveSpecdata_button_clicked()
{
    SavePositionSpectralData();

}

void MainWindow::on_get100PixDta_Button_clicked()
{
    ui->changeROI_ScrollBar->setValue(5);ui->ROI_label->setNum(5*2+1);
    //QMessageBox::information(this, "INFO","Select two points with 'ctrl + left click'");
    if(myHSI.selectPointNum>2){
        QMessageBox::warning(this, "WANRING","Selected points can only be two");
    }
    else if(myHSI.selectPointNum<2)
        QMessageBox::warning(this, "WANRING","Selected points can only be two");
    else{
        Save121PositionSpectralData();

    }
}

void MainWindow::on_SaveJPG_Button_clicked()
{
    if(myHSI.selectPointNum==0){
        backupimageHSI.create(cv::Size(imageHSI.cols,imageHSI.rows),CV_8UC3);
        backupimageHSI.setTo(cv::Scalar::all(0));
        imageHSI.copyTo(backupimageHSI);
    }
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Data"), "",tr("(*.jpg)"));
    QFile file(filePath);
    if(file.open(QFile::WriteOnly)){
        cv::imwrite(filePath.toStdString(),backupimageHSI);
        QMessageBox::information(this, "INFO","SAVE SUCCEED");
    }
    else {
        QMessageBox::warning(this, "WANRING","SAVE FAILED");
    }
}
