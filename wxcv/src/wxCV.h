//
// Created by Valerio Nogueira on 03/11/2020.
//

#ifndef ECOM_100_VISAO_COMPUTACIONAL_WXCV_H
#define ECOM_100_VISAO_COMPUTACIONAL_WXCV_H

#include <wx/app.h>
#include <wx/frame.h>


namespace wxcv {

    class wxCV : public wxApp {
    public:
        bool OnInit() override;
    };

    class MainWindow : public wxFrame {
    public:
        enum {
            ID_OPEN_IMAGE,
            ID_SAVE_IMAGE,
            ID_RESIZE_IMAGE,
            ID_FILTER_2D,
        };

        MainWindow();

        void InitMenu();
    };

}
#endif //ECOM_100_VISAO_COMPUTACIONAL_WXCV_H
