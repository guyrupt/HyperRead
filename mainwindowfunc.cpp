#include "mainwindow.h"
#include "ui_mainwindow.h"



void MainWindow::loadRawData(hsi2l &seeHSI){

    //--要跟程式說檔案格式(ios::binary))，這樣比較穩
//    ifstream ifile(myHSI.pathHSI.c_str(),ios::binary);
//    if(ifile==0){
//        QMessageBox::information(0, "Error!", "Need Raw Data file!");
//        return;
//    }

//    myHSI.dataCheck = true;

//    myHSI.rawDataHSI=new float**[myHSI.lines]();
//    float num;
//    for(int indx_L=0;indx_L<myHSI.lines;++indx_L){
//        myHSI.rawDataHSI[indx_L]=new float *[myHSI.bands]();
//        for(int indx_B=0;indx_B<myHSI.bands;++indx_B){
//            myHSI.rawDataHSI[indx_L][indx_B]=new float[myHSI.samples]();
//            for(int indx_S=0;indx_S<myHSI.samples;++indx_S){
//                ifile.read((char*) &num,4);
//                myHSI.rawDataHSI[indx_L][indx_B][indx_S]=num;
//            }
//        }
//        StatProgress->setValue(100*indx_L/myHSI.lines+1);
//    }

//    ifile.close();


    std::ifstream ifile(seeHSI.pathHSI.c_str(),std::ios::binary);
    if(!ifile){
        QMessageBox::information(0, "Error!", "Need Raw Data file!");
        return;
    }

    seeHSI.dataCheck = true;

    seeHSI.rawDataHSI=new float**[seeHSI.lines]();
    float num;
    for(int indx_L=0;indx_L<seeHSI.lines;++indx_L){
        seeHSI.rawDataHSI[indx_L]=new float *[seeHSI.bands]();
        for(int indx_B=0;indx_B<seeHSI.bands;++indx_B){
            seeHSI.rawDataHSI[indx_L][indx_B]=new float[seeHSI.samples]();
            for(int indx_S=0;indx_S<seeHSI.samples;++indx_S){
                ifile.read((char*) &num,4);
                seeHSI.rawDataHSI[indx_L][indx_B][indx_S]=num;
//                if (num > myHSI.reflectance_Max){
//                    myHSI.reflectance_Max = num;
//                }
            }
        }
        ui->StatProgress->setValue(100*(indx_L+1)/seeHSI.lines);
    }
    //qDebug()<<seeHSI.lines;
    ifile.close();

}

void MainWindow::readHyperspectralData(hsi2l &seeHSI){

    //-----------------------------//
    //--    讀取HDR檔案的資訊      --//
    std::ifstream in(seeHSI.pathHDR.c_str(),std::ios::in);
    //seeHSI.lines = ui->hisLineLength_lineEdit->text().toInt();
    std::string linetemp;//--用來比較字串
    char data[40];
    while (!in.eof()) {
        in>>data;
        linetemp=data;
        if(linetemp=="samples"){
            in >> data >> seeHSI.samples;//--該行的整數放到samples
        }
        if(linetemp=="lines"){
            in >> data >>seeHSI.lines_original;
            if(seeHSI.lines_original < seeHSI.lines){
                seeHSI.lines = seeHSI.lines_original;
            }
        }
        if(linetemp=="bands"){
            in >> data >> seeHSI.bands;
        }
    }//--END while
    in.close();

    seeHSI.showIamge.create(cv::Size(seeHSI.samples,seeHSI.lines),CV_8UC3);
    seeHSI.showIamge.setTo(cv::Scalar::all(0)) ;

    loadRawData(seeHSI);

    for(int y=0;y<seeHSI.showIamge.rows;++y){
        for(int x=0;x<seeHSI.showIamge.cols;++x){
            int val= seeHSI.rawDataHSI[y][seeHSI.bandCurrent][x]*ui->imgThreshold_ScrollBar->value();//--Line Band Sample
            if(val>255)
                val=255;
            if(val<0)
                val=0;

            seeHSI.showIamge.ptr<uchar>(y)[x*3]=val;
            seeHSI.showIamge.ptr<uchar>(y)[x*3+1]=val;
            seeHSI.showIamge.ptr<uchar>(y)[x*3+2]=val;
        }
    }



}

void MainWindow::GetPositionSpectral(int u, int v,int i){
    QLineSeries *specSeries = new QLineSeries();
    int rangeROI=ui->changeROI_ScrollBar->value();
    std::vector<float> selectTemp;
    selectTemp.reserve(myHSI.bands);
    for(int i=0;i<myHSI.bands;++i){
        if(rangeROI == 0){ //--只選單點pixel
            myHSI.single_ROISpectral.push_back(myHSI.rawDataHSI[v][i][u]);
        }
        else{
            for(int y=(-rangeROI);y<(rangeROI+1);++y){
                for(int x=(-rangeROI);x<(rangeROI+1);++x){
                    selectTemp.push_back(myHSI.rawDataHSI[v+y][i][u+x]);
                }
            }
            sort(selectTemp.begin(),selectTemp.end());//--排序目的為去min max //--由小排到大
            selectTemp.pop_back();//--在此band的ROI區域踢出max
            float sumValue=0.0;
            for(int i_vec=1;i_vec<selectTemp.size();++i_vec){
                sumValue=sumValue+selectTemp[i_vec];//--開始算總和，但是最小值不紀錄
            }
            sumValue=sumValue/(selectTemp.size()-1);
            myHSI.single_ROISpectral.push_back(sumValue);
            selectTemp.clear();
        }
    }
    for (int i=0;i<myHSI.bands;++i ) {
        specSeries->append(myHSI.spectralIndex[i],myHSI.single_ROISpectral[i]);
        //qDebug()<<myHSI.spectralIndex[i]<<myHSI.single_ROISpectral[i];
    }

    // ///////////////////////////////////////////

//    for (int i=0;i<myHSI.bands;++i ) {
//        stupid->append(myHSI.spectralIndex[i],0.5);
//    }
    specSeries->setName(QString("Point%1").arg(i+1));
    chart->addSeries(specSeries);

    chart->createDefaultAxes();


    myHSI.select_ROISpectral.push_back(myHSI.single_ROISpectral);
    myHSI.single_ROISpectral.clear();

}

void MainWindow::SavePositionSpectralData()
{
    vector<vector<float>> vecTemp;
    int rangeROI=ui->changeROI_ScrollBar->value();
    for(int j = 0;j<(int)myHSI.x_selectPoints.size();j++){
        vector<float> selectTemp;
        selectTemp.reserve(myHSI.bands);
        for(int i=0;i<myHSI.bands;++i){
            if(rangeROI == 0){ //--只選單點pixel
                myHSI.single_ROISpectral.push_back(myHSI.rawDataHSI[myHSI.y_selectPoints[j]][i][myHSI.x_selectPoints[j]]);
            }
            else{
                for(int y=(-rangeROI);y<(rangeROI+1);++y){
                    for(int x=(-rangeROI);x<(rangeROI+1);++x){
                        selectTemp.push_back(myHSI.rawDataHSI[myHSI.y_selectPoints[j]+y][i][myHSI.x_selectPoints[j]+x]);
                    }
                }
                sort(selectTemp.begin(),selectTemp.end());//--排序目的為去min max //--由小排到大
                selectTemp.pop_back();//--在此band的ROI區域踢出max
                float sumValue=0.0;
                for(int i_vec=1;i_vec<selectTemp.size();++i_vec){
                    sumValue=sumValue+selectTemp[i_vec];//--開始算總和，但是最小值不紀錄
                }
                sumValue=sumValue/(selectTemp.size()-1);
                myHSI.single_ROISpectral.push_back(sumValue);
                selectTemp.clear();
            }
        }
        vecTemp.push_back(myHSI.single_ROISpectral);
        myHSI.single_ROISpectral.clear();
    }
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save csv Data"), "",tr("(*.csv)"));
    QFile file(filePath);

    if(file.open(QFile::WriteOnly|QFile::Truncate|QFile::Text)){
        QTextStream out(&file);
        out << "point" << ",";
        out << "status" << ",";
        for (int j = 0; j < (int)myHSI.spectralIndex.size(); j++) {
            out << myHSI.spectralIndex[j]<<",";
        }
        out << "\n";
        for (int i = 0; i < (int)vecTemp.size(); i++){
            out << "point " << i + 1 << ",";
            if(myHSI.status[i]==1){
                out << "healthy" << ",";
            }
            else
                out << "sick" << ",";

            for (int j = 0; j < (int)vecTemp[i].size(); j++) {
                out << vecTemp[i][j]<<",";
            }
            out << "\n";
        }
        file.flush();
        file.close();
    }
    else {
        QMessageBox::warning(this, "WANRING","SAVE FAILED");
    }
}

void MainWindow::Save121PositionSpectralData()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save csv Data"), "",tr("(*.csv)"));
    QFile file(filePath);
    if(file.open(QFile::WriteOnly|QFile::Truncate|QFile::Text)){
        QTextStream out(&file);
        int rangeROI=ui->changeROI_ScrollBar->value();

        cv::rectangle(backupimageHSI,cv::Point(myHSI.x_selectPoints[0]-rangeROI,myHSI.y_selectPoints[0]-rangeROI),cv::Point(myHSI.x_selectPoints[0]+rangeROI,myHSI.y_selectPoints[0]+rangeROI),cv::Scalar(0,255,0),1);
        cv::putText(backupimageHSI,"1",
                    cv::Point(myHSI.x_selectPoints[0]-rangeROI,myHSI.y_selectPoints[0]+rangeROI+3),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(0,255,0));
        cv::rectangle(backupimageHSI,cv::Point(myHSI.x_selectPoints[1]-rangeROI,myHSI.y_selectPoints[1]-rangeROI),cv::Point(myHSI.x_selectPoints[1]+rangeROI,myHSI.y_selectPoints[1]+rangeROI),cv::Scalar(0,255,0),1);
        cv::putText(backupimageHSI,"2",
                    cv::Point(myHSI.x_selectPoints[1]-rangeROI,myHSI.y_selectPoints[1]+rangeROI+3),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(0,255,0));
        ui->showHSI_label->setPixmap(QPixmap::fromImage(QImage(backupimageHSI.data
                                                                       ,backupimageHSI.cols,backupimageHSI.rows,QImage::Format_RGB888)));

        out << "Region"<<",";
        for (int j = 0; j < (int)myHSI.spectralIndex.size(); j++) {
            out << myHSI.spectralIndex[j]<<",";
        }
        out << "\n";
        for(int y=(-rangeROI);y<(rangeROI+1);++y){
            for(int x=(-rangeROI);x<(rangeROI+1);++x){
                out << "Region 1" << ",";
                for(int i=0;i<myHSI.bands;++i){
                    out << myHSI.rawDataHSI[myHSI.y_selectPoints[0]+y][i][myHSI.x_selectPoints[0]+x]<<",";
                }
                out << "\n";
            }
        }
        for(int y=(-rangeROI);y<(rangeROI+1);++y){
            for(int x=(-rangeROI);x<(rangeROI+1);++x){
                out << "Region 2" << ",";
                for(int i=0;i<myHSI.bands;++i){
                    out << myHSI.rawDataHSI[myHSI.y_selectPoints[1]+y][i][myHSI.x_selectPoints[1]+x]<<",";
                }
                out << "\n";
            }
        }
        file.flush();
        file.close();
        ui->showHSI_label->setPixmap(QPixmap::fromImage(QImage(backupimageHSI.data
                                                                       ,backupimageHSI.cols,backupimageHSI.rows,QImage::Format_RGB888)));
    }
    else
        QMessageBox::warning(this, "WANRING","SAVE FAILED");




}
