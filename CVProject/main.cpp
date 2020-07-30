
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Mat starMap = imread("StarMap.png", 0);
Mat rotatedArea = imread("Small_area_rotated.png", 0);
Mat area = imread("Small_area.png", 0);

int main(int argc, const char * argv[]) {
    
    if (starMap.empty() || rotatedArea.empty() || area.empty()) {
        cout << "Image reading is failed." << endl;
        return 0;
    }
    
    Mat result;
    
    int result_cols =  starMap.cols - area.cols + 1;
    int result_rows = starMap.rows - area.rows + 1;

    result.create( result_rows, result_cols, CV_32FC1 );
    matchTemplate( starMap, area, result, 0);
    double minVal; double maxVal; Point minLoc; Point maxLoc;

    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    cout<<minLoc.x<<" "<<minLoc.y<<endl;
    cout<<minVal<<endl;
    return 0;
}
