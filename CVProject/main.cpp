
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

void compareByRotating(Mat container, Mat sample){
    Mat result;
    bool exactMatchingFound = false;
    int result_cols =  container.cols - sample.cols + 1;
    int result_rows = container.rows - sample.rows + 1;

    result.create( result_rows, result_cols, CV_32FC1 );
    double minVal; double maxVal; Point minLoc; Point maxLoc;

    for (int i = 0; i < 360; i++) {
        double angle = (double)i;
        Point2f center(0.0, 0.0);
        Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
        Rect2f bbox = cv::RotatedRect(cv::Point2f(), container.size(), angle).boundingRect2f();
        rot.at<double>(0,2) += bbox.width/2.0 - container.cols/2.0;
        rot.at<double>(1,2) += bbox.height/2.0 - container.rows/2.0;

        Mat dst;
        warpAffine(container, dst, rot, bbox.size());
        
        matchTemplate( dst, sample, result, 0);
        minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
        if (minVal == 0) {
            cout<<"Rotating angle: "<<angle<<endl;
            cout<<minLoc.x<<","<<minLoc.y<<"--";
            cout<<minLoc.x<<","<<minLoc.y + sample.cols<<"--";
            cout<<minLoc.x + sample.rows<<","<<minLoc.y<<"--";
            cout<<minLoc.x + sample.rows<<","<<minLoc.y + sample.cols<<endl;
            exactMatchingFound = true;
            break;
        }
    }
    if (!exactMatchingFound) {
        cout<<"Exact matching is not found"<<endl;
    }
}

int main(int argc, const char * argv[]) {
    
    Mat starMap = imread("StarMap.png", 0);
    Mat rotatedArea = imread("Small_area_rotated.png", 0);
    Mat area = imread("Small_area.png", 0);
    
    if (starMap.empty() || rotatedArea.empty() || area.empty()) {
        cout << "Image reading is failed." << endl;
        return 0;
    }
    
    cout<<"Result for small area:"<<endl;
    compareByRotating(starMap, area);
    cout<<endl;
    cout<<"Result for rotated area:"<<endl;
    compareByRotating(starMap, rotatedArea);
    
    return 0;
}
