//
// Created by Valerio Nogueira on 03/11/2020.
//

#ifndef ECOM_100_VISAO_COMPUTACIONAL_WXCV_H
#define ECOM_100_VISAO_COMPUTACIONAL_WXCV_H

#include <opencv2/opencv.hpp>
#include <wx/app.h>
#include <wx/frame.h>

#include "wxCvImagePanel.h"


namespace wxcv {

    class wxCV : public wxApp {
    public:
        bool OnInit() override;
    };

    class MainWindow : public wxFrame {
        cv::Mat image;
        wxCvImagePanel* imagePanel;
    public:
        /*
         * Widgets id's
         */
        enum {
            ID_OPEN_IMAGE,
            ID_SAVE_IMAGE,
            ID_RESIZE_IMAGE,
            ID_FILTER_2D,
            ID_THRESHOLD,
        };

        /*
         * Main window constructor
         */
        MainWindow();

        /*
         * Initialize the menu bar
         */
        void InitMenu();

        /*
         * Bind main window's events
         */
        void BindEvents();

        /*
         * Open an image from disk
         */
        void OpenImage(wxCommandEvent& event);

        /*
         * Save @image to disk
         */
        void SaveImage(wxCommandEvent& event);

        /*
         * Quit the application
         */
        void Exit(wxCommandEvent& event);

        /*
         * Resize @image
         */
        void ResizeImage(wxCommandEvent& event);

        /*
         * Apply a 2D filter defined by the user to @image
         */
        void Filter2D(wxCommandEvent& event);

        /*
         * Apply a threshold to @image
         */
        void Threshold(wxCommandEvent& event);

        /*
         * Show about information
         */
        void About(wxCommandEvent& event);
    };

}
#endif //ECOM_100_VISAO_COMPUTACIONAL_WXCV_H
