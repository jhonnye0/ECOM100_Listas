//
// Created by Valerio Nogueira on 07/11/2020.
//

#include "wxCvThresholdDialog.h"
#include <wx/sizer.h>


namespace wxcv {

    wxCvThresholdDialog::wxCvThresholdDialog(wxWindow* parent, cv::Mat& image) :
            wxDialog(parent, wxID_ANY, wxT("Limiar")) {
        threshInput = new wxTextCtrl(this, ID_THRESH, "0");
        maxValInput = new wxTextCtrl(this, ID_MAXVAL, "255");
        type = new wxChoice(this, ID_TYPE);
        for(auto& c : {wxT("THRESH_BINARY"), wxT("THRESH_BINARY_INV"), wxT("THRESH_TRUNC"),
                       wxT("THRESH_TOZERO"), wxT("THRESH_TOZERO_INV")}){
            type->Append(c);
        }

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

        box->Add(threshInput, 0, wxEXPAND | wxALL, 5);
        box->Add(maxValInput, 0, wxEXPAND | wxALL, 5);
        box->Add(type, 0, wxEXPAND | wxALL, 5);
        box->Add(bottom, 1, wxEXPAND);
        box->Add(wxDialog::CreateButtonSizer(wxOK | wxCANCEL), 0, wxALIGN_CENTER | wxALL, 5);
        SetSizer(box);

        Center();
        Layout();

        Bind(wxEVT_TEXT, &wxCvThresholdDialog::Preview, this, ID_THRESH);
        Bind(wxEVT_TEXT, &wxCvThresholdDialog::Preview, this, ID_MAXVAL);
        Bind(wxEVT_CHOICE, &wxCvThresholdDialog::Preview, this, ID_TYPE);
    }


    /*
     * Calculate the convolution of image with kernel, storing the result in image
     */
    bool wxCvThresholdDialog::Apply(cv::Mat& image) {
        if (image.empty()) {
            return false;
        }

        cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);
        cv::cvtColor(image, image, cv::COLOR_GRAY2RGB);

        double thresh, maxVal;
        threshInput->GetValue().ToDouble(&thresh);
        maxValInput->GetValue().ToDouble(&maxVal);

        cv::threshold(image, image, thresh, maxVal, type->GetSelection());

        return true;
    }


    /*
     *
     */
    void wxCvThresholdDialog::Preview(wxCommandEvent& event) {
        cv::cvtColor(originalImage, previewImage, cv::COLOR_RGB2GRAY);
        cv::cvtColor(previewImage, previewImage, cv::COLOR_GRAY2RGB);

        double thresh, maxVal;
        threshInput->GetValue().ToDouble(&thresh);
        maxValInput->GetValue().ToDouble(&maxVal);

        cv::threshold(previewImage, previewImage, thresh, maxVal, cv::THRESH_BINARY + type->GetSelection());

        preview->UpdateImage(previewImage);
    }
}