//
// Created by Valerio Nogueira on 07/11/2020.
//

#include "wxCvFilter2dDialog.h"
#include <wx/sizer.h>


namespace wxcv {

    wxCvFilter2dDialog::wxCvFilter2dDialog(wxWindow* parent, cv::Mat& image) :
            wxDialog(parent, wxID_ANY, wxT("Filtrar")) {
        kernel = cv::Mat(1, 1, CV_32FC1, 1.0f);
        input = new wxTextCtrl(this, ID_INPUT, "1", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
        grayscale = new wxCheckBox(this, ID_GRAYSCALE, wxT("Tons de cinza"));
        original = new wxCvImagePanel(this);
        preview = new wxCvImagePanel(this);

        float aspect = image.size().aspectRatio();
        float factor = 1.0f * previewMaxSize / (aspect > 1.0f ? image.size().width : image.size().height);

        cv::resize(image, originalImage, cv::Size(), factor, factor);

        original->UpdateImage(originalImage);
        preview->UpdateImage(originalImage);

        wxBoxSizer* bottom = new wxBoxSizer(wxHORIZONTAL);
        bottom->Add(original, 1, wxEXPAND | wxALL, 5);
        bottom->Add(preview, 1, wxEXPAND | wxALL, 5);

        wxBoxSizer* box = new wxBoxSizer(wxVERTICAL);
        box->Add(input, 1, wxEXPAND | wxALL, 5);
        box->Add(grayscale, 0, wxALL, 5);
        box->Add(bottom, 1, wxEXPAND);
        box->Add(wxDialog::CreateButtonSizer(wxOK | wxCANCEL), 0, wxALIGN_CENTER | wxALL, 5);
        SetSizer(box);

        Center();
        Layout();

        Bind(wxEVT_TEXT, &wxCvFilter2dDialog::Preview, this, ID_INPUT);
        Bind(wxEVT_CHECKBOX, &wxCvFilter2dDialog::Preview, this, ID_GRAYSCALE);
    }


    /*
     * Calculate the convolution of image with kernel, storing the result in image
     */
    bool wxCvFilter2dDialog::Apply(cv::Mat& image) {
        if (image.empty()) {
            return false;
        }

        if(grayscale->IsChecked()){
            // Converts  the image to grayscale and then back to rgb (3 channels)
            cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);
            cv::cvtColor(image, image, cv::COLOR_GRAY2RGB);
        }
        cv::filter2D(image, image, -1, kernel);

        return true;
    }


    int countColumns(const char* s){
        int cols = 0;
        for(int i = 0;s[i] != '\n' && s[i];){
            if(s[i] == ' '){
                cols++;
                while(s[i] == ' '){
                    i++;
                }
            }
            else {
                i++;
            }
        }

        return cols + 1;
    }

    /*
     *
     */
    void wxCvFilter2dDialog::Preview(wxCommandEvent& event) {
        std::string raw = input->GetValue().Trim().ToStdString();
        int rows = !raw.empty() ? 1 : 0;
        int cols = 0;

        for(int i = 0;raw[i];i++){
            if(raw[i] == '\n'){
                rows++;
            }
        }

        cols = countColumns(raw.c_str());

        if(rows == 0 || cols == 0){
            std::cout << "INVALID INPUT!!!" << std::endl;
            return;
        }

        std::cout << "Kernel size: " << cv::Size(cols, rows) << std::endl;

        cv::resize(kernel, kernel, cv::Size(cols, rows));
        std::stringstream stringstream(raw);
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < cols;j++){
                float value;
                stringstream >> value;
                kernel.at<float>(i, j) = value;
            }
        }

        if(grayscale->IsChecked()){
            cv::cvtColor(originalImage, previewImage, cv::COLOR_RGB2GRAY);
            cv::cvtColor(previewImage, previewImage, cv::COLOR_GRAY2RGB);
        }
        else {
            originalImage.copyTo(previewImage);
        }

        cv::filter2D(previewImage, previewImage, -1, kernel);

        preview->UpdateImage(previewImage);
    }
}