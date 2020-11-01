//
// Created by Valerio Nogueira on 31/10/2020.
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include "common.h"

#define CVUI_IMPLEMENTATION

#include "cvui.h"

#define WINDOW_NAME "Kernel"
#define KEY_EXIT 27


void updateKernelSize(cv::Mat& frame, int& kernelSize, std::vector<std::vector<int>>& kernel) {
    if (kernelSize > kernel.size()) {
        for (int i = 0;i < kernelSize;i++) {
            if (i < kernel.size()) {
                for (int j = kernel.size();j < kernelSize;j++) {
                    kernel[i].push_back(0);
                }
            }
            else {
                kernel.push_back(std::vector<int>(kernelSize, 0));
            }
        }
    }
    else {
        kernel.resize(kernelSize);
        for (int i = 0;i < kernelSize;i++) {
            kernel[i].resize(kernelSize);
        }
    }
}

void displayKernel(int xOffset, int yOffset, cv::Mat& frame, int kernelSize, std::vector<std::vector<int>>& kernel){
    const int rowWidth = 100;
    const int rowHeight = 25;

    for (int i = 0;i < kernelSize;i++) {
        cvui::beginRow(frame, xOffset, yOffset + rowHeight * i);
        for (int j = 0;j < kernelSize;j++) {
            cvui::beginColumn(rowWidth, rowHeight);
            cvui::counter(&kernel[i][j]);
            cvui::endColumn();
        }
        cvui::endRow();
    }
}

int main() {
    bool showGUI = true;
    int key = 0;
    int kernelSize = 1;
    std::vector<std::vector<int>> kernel;
    cv::Mat image;
    cv::Mat frame(480, 640, CV_32F);
    cv::Mat kernelMat(1, 1, CV_32F);

    cvui::init(WINDOW_NAME);
    // Cria a matriz kernelSize x kernelSize de zeros
    kernel = std::vector<std::vector<int>>(kernelSize, std::vector<int>(kernelSize, 0));

    while (key != KEY_EXIT) {
        // Caso alguma imagem esteja aberta copia ela para o frame e pinta de cinza caso contrario
        if(!image.empty()){
            cv::resize(image, frame, frame.size());
            cv::filter2D(frame, frame, -1, kernelMat);
        }
        else {
            frame = cv::Scalar(.2f, .2f, .2f);
        }

        cvui::window(frame, 0, 0, 300, showGUI ? 150 + kernelSize * 25 : 50,
                     "Kernel");
        showGUI = cvui::checkbox(frame, 10, 25, "Mostrar GUI", &showGUI);
        if(showGUI) {
            if (cvui::button(frame, 10, 80 + kernelSize * 25 + 10, "Abrir imagem")) {
                if (loadImage(image) && !image.empty()) {
                    image.convertTo(image, CV_32F);
                    std::cout << "Loaded image type: " << getImgType(image.type()) << std::endl;
                    cv::resize(image, frame, frame.size());
                }
            }
            if (cvui::button(frame, 10, 80 + kernelSize * 25 + 40, "Salvar imagem")) {
                if (!image.empty()) {
                    cv::resize(image, frame, frame.size());
                    cv::filter2D(frame, frame, -1, kernelMat);
                    saveImage(frame);
                }
            }
            cvui::beginRow(frame, 10, 50);
            cvui::printf("Kernel size");
            cvui::counter(&kernelSize, 2);
            cvui::endRow();
            updateKernelSize(frame, kernelSize, kernel);
            displayKernel(12, 80, frame, kernelSize, kernel);
        }
        cv::resize(kernelMat, kernelMat, {kernelSize, kernelSize});
        for(int i = 0;i < kernelSize;i++){
            for(int j = 0;j < kernelSize;j++){
                kernelMat.at<FLOAT>(i, j) = kernel[i][j];
            }
        }

        cvui::update(WINDOW_NAME);
        frame.convertTo(frame, CV_8U);
        cv::imshow(WINDOW_NAME, frame);

        key = cv::waitKey(1);
    }

    cv::destroyWindow(WINDOW_NAME);

    return 0;
}