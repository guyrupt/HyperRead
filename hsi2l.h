#ifndef HSI2L_H
#define HSI2L_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <memory.h>

#include "opencv.hpp"
#include "weichang2l.h"

class hsi2l
{
public:
    hsi2l();
    void initHSI2l();
    void releaseDataHSI();
    float ***rawDataHSI;//--lines-bands-samples(LBS)
    //float reflectance_Max; //--  max reflectance in the data
    int lines;  //--user sets lines
    int samples;//--total samples
    int bands;  //--total bands
    int lines_original; //--total lines
    int bandCurrent;
    bool dataCheck; //--確認檔案是否有讀到檔案
    bool start2select;  //--管理滑鼠事件(左鍵)
    bool singleSelectSpectral;//--滑鼠事件:是否顯示光譜
    bool discriminantCheck;//-- LDA 啟用
    bool removeBackground;
    int selectCut_A;
    int selectCut_B;
    int resultLDA; //--LDA辨識結果
    int selectPointNum; //--使用者所選擇點數量
    int standard_WB; //-- 0: 無任何動作(按鈕:blue)  1: 白校正  2:黑校正
                     //--按鈕顏色:blue is 重新or無動作  yellow is 等在取光譜  green is 取完光譜
    std::string pathHDR; //--HDR 檔案路徑
    std::string pathHSI; //--Raw data 檔案路徑
    std::string _FilePath;
    std::string _FileName;//--存放檔案的名稱
    cv::Mat showIamge; //--顯示高光譜影像
    cv::Mat resultImage; //-- 顯示LDA辨識病害得結果

    std::vector< std::vector<float> > select_ROISpectral;
    std::vector< float >single_ROISpectral;

    std::vector<float> x_stdHomography;//--Homography的基準校正點
    std::vector<float> y_stdHomography;
    std::vector<int> x_selectPoints;
    std::vector<int> y_selectPoints;
    std::vector<float> standard_W;
    std::vector<float> standard_B;
    std::vector<cv::Point2i> clickPoints;
    std::vector<int> clickRangeROI;
    std::vector<float> spectralIndex;//--放置波長代碼
    std::vector<int> status;
    std::string float2str(float x);
    std::string int2str(int x);



};

#endif // HSI2L_H
