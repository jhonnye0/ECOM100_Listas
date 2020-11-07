//
// Created by Valerio Nogueira on 07/11/2020.
//

#ifndef WXCV_WXCVFILTER2DDIALOG_H
#define WXCV_WXCVFILTER2DDIALOG_H

#include <opencv2/opencv.hpp>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include "wxCvImagePanel.h"


namespace wxcv {

    class wxCvFilter2dDialog : public wxDialog {
        wxTextCtrl* input;
        wxCvImagePanel* original;
        wxCvImagePanel* preview;
        wxCheckBox* grayscale;
        cv::Mat originalImage;
        cv::Mat previewImage;
        cv::Mat kernel;

        const static int previewMaxSize = 300;
    public:
        enum {
            ID_INPUT,
            ID_GRAYSCALE
        };

        wxCvFilter2dDialog(wxWindow* parent, cv::Mat& image);

        /*
         * Filter image using kernel
         */
        bool Apply(cv::Mat& image);

        /*
         * Parse the input and apply the filter in the preview image
         */
        void Preview(wxCommandEvent& event);
    };

}

#endif //WXCV_WXCVFILTER2DDIALOG_H
