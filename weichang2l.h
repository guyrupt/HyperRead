// helper class from senior 
#ifndef WEICHANG2L_H
#define WEICHANG2L_H
//-- Wei-Chang Chung 2013-05-20
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <numeric>

#include "opencv.hpp"

using namespace std;
//using namespace cv;

const double PI = 3.14159265;

class WeiChang2L
{
public:
    WeiChang2L();
    ~WeiChang2L();//--暫時不會用到

    string float2str(float x);
    string int2str(int x);
    void SolveEquations(float pt1_x, float pt1_y, float pt2_x, float pt2_y, float &ans_a, float &ans_b);
    void gray2color(double I,double &colorR,double &colorG,double &colorB);
    void cube2img(float ***in_cube, cv::Mat &out_Img, int Line, int Sample, int get_Band, int showImg);
    void img2cube(float ***out_cube, cv::Mat &in_Img, int Line, int Sample, int put_Band);

    float ***wccDataHSI;
    template <class T> T medianFilter(T N1, T N2, T N3){
        vector<T> sortNum;
        sortNum.push_back(N1);
        sortNum.push_back(N2);
        sortNum.push_back(N3);
        sort(sortNum.begin(),sortNum.end());
        return sortNum[1];
        //sortNum.clear();
    }
    template <class T> T medianFilter_v2(std::vector<T> num_set){
        //-- 注意: element要為奇數
        sort(num_set.begin(),num_set.end());//--由小排到大
        return num_set[(num_set.size()+1)/2-1];
    }
    template <class T> T meanFilter(T N1, T N2, T N3){
        return (N1+N2+N3)/3; //-- 注意整數的問題
    }

    template <class T> T meanFilter_v2(std::vector<T> num_set){
        T num_Mean = accumulate( num_set.begin(), num_set.end(), 0.0 );
        num_Mean = num_Mean*1.0/num_set.size()*1.0;
        //qDebug()<<"size: "<<num_set.size();
        return num_Mean;
    }


    template <class T> T ***Create3D(int N1, int N2, int N3){

        T *** array = new T ** [N1]();

        array[0] = new T * [N1*N2]();

        array[0][0] = new T [N1*N2*N3]();

        //int i,j,k;
        int i,j;
        for( i = 0; i < N1; i++) {

            if (i < N1 -1 ) {

                array[0][(i+1)*N2] = &(array[0][0][(i+1)*N3*N2]);

                array[i+1] = &(array[0][(i+1)*N2]);

            }

            for( j = 0; j < N2; j++) {
                if (j > 0) array[i][j] = array[i][j-1] + N3;
            }

        }

        return array;
    }

    template <class T> void Delete3D(T ***array) {
        delete[] array[0][0];
        delete[] array[0];
        delete[] array;
        array = NULL;
        cout<<"...........Release 3D array..........."<<std::endl;
    }

};

#endif // WEICHANG2L_H
