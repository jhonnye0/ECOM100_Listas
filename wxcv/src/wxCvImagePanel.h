//
// Created by Valerio Nogueira on 04/11/2020.
//

#ifndef WXCV_WXCVIMAGEPANEL_H
#define WXCV_WXCVIMAGEPANEL_H

#include <wx/bitmap.h>
#include <wx/frame.h>
#include <wx/image.h>
#include <wx/panel.h>
#include <opencv2/opencv.hpp>

class wxCvImagePanel : public wxPanel
{
    wxImage image;
    wxBitmap resized;
    int w, h;

public:
    wxCvImagePanel(wxWindow* parent);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void OnSize(wxSizeEvent& event);
    void render(wxDC& dc);

    void UpdateImage(cv::Mat& _image);

    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

DECLARE_EVENT_TABLE()
};

#endif //WXCV_WXCVIMAGEPANEL_H
