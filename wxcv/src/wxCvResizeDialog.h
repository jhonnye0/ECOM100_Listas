//
// Created by Valerio Nogueira on 03/11/2020.
//

#ifndef WXCV_WXCVRESIZEDIALOG_H
#define WXCV_WXCVRESIZEDIALOG_H

#include <opencv2/opencv.hpp>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>


namespace wxcv {

    class wxCvResizeDialog : public wxDialog {
        enum {
            ID_INTERPOLATION,
            ID_UNIT,
            ID_X,
            ID_Y,
        };

        enum Unit {
            Pixel,
            Percentage
        };

        static const wxString INTERPOLATION_CHOICES[];
        static const wxString RESIZE_UNIT_CHOICES[];

        int imageWidth;
        int imageHeight;
        wxChoice* interpolation;
        wxChoice* unit;
        wxTextCtrl* x;
        wxTextCtrl* y;
    public:
        /*
         * Default constructor
         */
        wxCvResizeDialog(wxWindow* parent, const cv::Mat& image);

        /*
         * Resize @image
         */
        bool Apply(cv::Mat& image);

        /*
         * Validate the input
         */
        bool Validate();

        /*
         * Convert the x and y values between px and % units
         */
        void OnUnitChanged(wxCommandEvent& event);
    };

}

#endif //WXCV_WXCVRESIZEDIALOG_H
