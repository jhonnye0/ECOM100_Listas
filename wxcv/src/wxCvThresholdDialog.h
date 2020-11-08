//
// Created by Valerio Nogueira on 07/11/2020.
//

#ifndef WXCV_WXCVTHRESHOLDDIALOG_H
#define WXCV_WXCVTHRESHOLDDIALOG_H

#include <opencv2/opencv.hpp>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include "wxCvImagePanel.h"


namespace wxcv {

    class wxCvThresholdDialog : public wxDialog {
        wxTextCtrl* threshInput;
        wxTextCtrl* maxValInput;
        wxChoice* type;
        wxCvImagePanel* original;
        wxCvImagePanel* preview;
        cv::Mat originalImage;
        cv::Mat previewImage;

        const static int previewMaxSize = 300;
    public:
        enum {
            ID_THRESH,
            ID_MAXVAL,
            ID_TYPE,
        };

        wxCvThresholdDialog(wxWindow* parent, cv::Mat& image);

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

#endif //WXCV_WXCVTHRESHOLDDIALOG_H
