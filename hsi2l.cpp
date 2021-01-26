#include "hsi2l.h"

hsi2l::hsi2l()
{

}

void hsi2l::initHSI2l()
{
    _FilePath.clear();
    _FileName.clear();
    //lines=1690;  //--user sets lines
    samples=0;//--total samples
    bands=0;  //--total bands
    lines_original=0; //--total lines
    bandCurrent=76; //--第一個位置的數值為0
    dataCheck = false;
    selectPointNum = 0;
    singleSelectSpectral = false;
    removeBackground = false;
    selectCut_A = 14;
    selectCut_B = 118;
//    grid = new QwtPlotGrid();
//    curve = new QwtPlotCurve();
    spectralIndex.clear();
    //reflectance_Max = 0.0;

}

void hsi2l::releaseDataHSI()
{
    //--釋放記憶體 (高光譜檔案)

    if(dataCheck == true){
        for(int i=0;i<lines;++i){
            for(int j=0;j<bands;++j){
                delete [] rawDataHSI[i][j];
            }
            delete [] rawDataHSI[i];
        }
        delete [] rawDataHSI;

        rawDataHSI=nullptr;
        dataCheck = false;

        x_stdHomography.clear();
        y_stdHomography.clear();
        standard_W.clear();
        standard_B.clear();
        clickPoints.clear();
        clickRangeROI.clear();
        spectralIndex.clear();

        std::cout<<"........Release DataHSI Memory........."<<std::endl;
    }

//    if(spectraCurve.size()!=0){
//        for(size_t i=0;i<spectraCurve.size();++i){
//            delete spectraCurve[i];
//        }
//        spectraCurve.clear();
//    }

}

std::string hsi2l::float2str(float x){//--原函式名稱oneSay

    std::stringstream str;
    std::string say;
    str<<x;
    str>>say;

    return say;
}

std::string hsi2l::int2str(int x){//--原函式名稱oneSay

    std::stringstream str;
    std::string say;
    str<<x;
    str>>say;

    return say;
}

