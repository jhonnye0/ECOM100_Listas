#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main()
{
    int n;

    Mat img;
    img = imread("second_frame.jpg");

    std::cout << "Digite o n da matriz (nxn)" << std::endl;
    std::cin >> n;

    Mat kernel(n, n, CV_32F);

    for(int i=0; i < n; i++)
    {
        for(int j=0; j < n; j++)
        {
            float value;
            std::cin >> value;
            kernel.at<float>(i,j) = value;
        }
    }

    std::cout << kernel << std::endl;

    cvtColor(img, img, COLOR_BGR2GRAY);
    filter2D(img, img, -1, kernel);

    imshow("Resultado", img);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
