#include "weichang2l.h"

WeiChang2L::WeiChang2L()
{
}

WeiChang2L::~WeiChang2L()
{
}

std::string WeiChang2L::float2str(float x){//--原函式名稱oneSay

    std::stringstream str;
    std::string say;
    str<<x;
    str>>say;

    return say;
}

std::string WeiChang2L::int2str(int x){//--原函式名稱oneSay

    std::stringstream str;
    std::string say;
    str<<x;
    str>>say;

    return say;
}

void WeiChang2L::SolveEquations(float pt1_x, float pt1_y, float pt2_x, float pt2_y, float &ans_a, float &ans_b){
    //-- 二元一次方程式，求解a,b
    //-- (ans_a)*(pt1_x) + (ans_b) = pt1_y ==> 方程式一
    //-- (ans_a)*(pt2_x) + (ans_b) = pt2_y ==> 方程式二
    //-- [ans_a ans_b] = inv([pt1_x 1;pt2_x 1])*[pt1_y ; pt2_y]; 以矩陣求解

    if(pt1_x - pt2_x != 0){
        ans_a = (pt1_y - pt2_y) / (pt1_x - pt2_x);
        ans_b = (pt1_x*pt2_y - pt2_x*pt1_y) / (pt1_x - pt2_x);
    }
    else{ //--這邊有待討論(因為分母為零的關係)
        ans_a = 0;
        ans_b = 0;
    }

}

void WeiChang2L::gray2color(double I,double &colorR,double &colorG,double &colorB){
    //--沒有避免灰階強度爆炸的狀況
    //    input:
    //        I,
    //                gray scale: 0 ~ 1;
    //    output:
    //        colorR
    //        colorG
    //        colorB
    //                color scale: 0 ~ 255;

    if (I > 1.0)
        I = 1.0;
    if (I < 0.0)
        I = 0.0;

//    colorR=255*((cos(I*2.0*PI)+1)/2.0);
//    colorG=255*((cos(I*2.0*PI+PI/4)+1)/2.0);
//    colorB=255*((sin(I*2.0*PI)+1)/2.0);

    colorR = 255*((-sin(I*2.0*PI)+1)/2.0);
    colorG = 255*((sin(I*2.0*PI-PI/2)+1)/2.0);
    colorB = 255*((sin(I*2.0*PI)+1)/2.0);
    if(I*255>190){colorB=0;}

}

void WeiChang2L::cube2img(float ***in_cube, cv::Mat &out_Img, int Line, int Sample, int get_Band, int showImg){

    //========= 將高光譜的data cube 轉成影像 =============//
    //-- in_cube : hyperspectral data cube
    //-- out_Img: output image
    //-- get_Band: 想要哪個 band 的影像

    out_Img.create(cv::Size(Sample,Line),CV_32FC3);

    for(int indx_L=0;indx_L<Line;++indx_L){
        for(int indx_S=0;indx_S<Sample;++indx_S){
            out_Img.ptr<float>(indx_L)[indx_S*3]  = in_cube[indx_L][get_Band][indx_S];
            out_Img.ptr<float>(indx_L)[indx_S*3+1]= in_cube[indx_L][get_Band][indx_S];
            out_Img.ptr<float>(indx_L)[indx_S*3+2]= in_cube[indx_L][get_Band][indx_S];

        }
    }

    if(showImg >= 1){//-- 想要看的波段影像
        std::string nameBand = "Get band_";
        nameBand = nameBand + int2str(get_Band);
        cv::imshow(nameBand,out_Img);
    }
}
