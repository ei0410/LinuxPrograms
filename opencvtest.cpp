#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
     
int main(int argc, char** argv ) 
{
    Mat image = imread("purin.jpeg");

    if(! image.data ) {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }

    namedWindow("image", WINDOW_AUTOSIZE);
    imshow("image", image);
                                               
    waitKey(0);
    destroyAllWindows();
    return 0;
}
