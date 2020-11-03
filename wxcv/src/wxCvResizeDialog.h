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
            ID_RESIZE_MODE,
            ID_X,
            ID_Y,
        };

        static const wxString INTERPOLATION_CHOICES[];
        static const wxString RESIZE_MODE_CHOICES[];

        wxChoice* interpolation;
        wxChoice* resizeMode;
        wxTextCtrl* x;
        wxTextCtrl* y;
    public:
        /*
         * Default constructor
         */
        wxCvResizeDialog(wxWindow* parent);

        /*
         * Resize @image
         */
        bool Apply(cv::Mat& image);

        /*
         * Validate the input
         */
        bool Validate();
    };

}

#endif //WXCV_WXCVRESIZEDIALOG_H
