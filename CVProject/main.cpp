
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    
    Mat image = imread("StarMap.png", 0);
    
    if (image.empty())
    {
        cout << "!!! Failed imread(): image not found" << std::endl;
        // don't let the execution continue, else imshow() will crash.
    }
    cout << "Hello, World!\n";
    return 0;
}
