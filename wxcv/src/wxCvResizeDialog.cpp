//
// Created by Valerio Nogueira on 03/11/2020.
//

#include "wxCvResizeDialog.h"
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/stattext.h>


namespace wxcv {

    const wxString wxCvResizeDialog::INTERPOLATION_CHOICES[] = {"INTER_NEAREST", "INTER_LINEAR", "INTER_CUBIC",
                                                                "INTER_AREA", "INTER_LANCZOS4", "INTER_LINEAR_EXACT",
                                                                "INTER_NEAREST_EXACT", "INTER_MAX",
                                                                "WARP_FILL_OUTLIERS", "WARP_INVERSE_MAP"};
    const wxString wxCvResizeDialog::RESIZE_MODE_CHOICES[] = {"Absoluto", "Relativo"};

    wxCvResizeDialog::wxCvResizeDialog(wxWindow* parent) : wxDialog(parent, wxID_ANY, wxT("Redimensionar imagem"),
                                                                    wxDefaultPosition, wxDefaultSize,
                                                                    wxDEFAULT_DIALOG_STYLE) {
        interpolation = new wxChoice(this, ID_INTERPOLATION);
        for (auto& choice : INTERPOLATION_CHOICES) {
            interpolation->Append(choice);
        }
        interpolation->SetSelection(0);

        resizeMode = new wxChoice(this, ID_RESIZE_MODE);
        for (auto& choice : RESIZE_MODE_CHOICES) {
            resizeMode->Append(choice);
        }
        resizeMode->SetSelection(0);

        x = new wxTextCtrl(this, ID_X);
        y = new wxTextCtrl(this, ID_Y);

        wxFlexGridSizer* flexGrid = new wxFlexGridSizer(2, wxSize(5, 5));

        flexGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Interpolação")));
        flexGrid->Add(interpolation, 1, wxEXPAND);
        flexGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Modo")));
        flexGrid->Add(resizeMode, 1, wxEXPAND);
        flexGrid->Add(new wxStaticText(this, wxID_ANY, wxT("x")));
        flexGrid->Add(x, 1, wxEXPAND);
        flexGrid->Add(new wxStaticText(this, wxID_ANY, wxT("y")));
        flexGrid->Add(y, 1, wxEXPAND);
        flexGrid->AddStretchSpacer();
        flexGrid->Add(new wxButton(this, wxID_OK), 1);

        wxBoxSizer* box = new wxBoxSizer(wxVERTICAL);
        box->Add(flexGrid, 1, wxEXPAND | wxALL, 5);
        SetSizer(box);
        Layout();
        Fit();
        Center();
    }


    /*
     * Resize @image according to the dimensions/proportions specified by the user
     */
    bool wxCvResizeDialog::Apply(cv::Mat& image) {
        if (Validate()) {
            int interpolationIndex = cv::INTER_LINEAR + interpolation->GetSelection();
            if (resizeMode->GetStringSelection() == "Absoluto") {
                long w, h;
                x->GetValue().ToLong(&w);
                y->GetValue().ToLong(&h);
                cv::resize(image, image, cv::Size(w, h), 0.0, 0.0, interpolationIndex);
            }
            else if (resizeMode->GetStringSelection() == "Relativo") {
                double fx, fy;
                x->GetValue().ToDouble(&fx);
                y->GetValue().ToDouble(&fy);
                cv::resize(image, image, cv::Size(), fx, fy, interpolationIndex);
            }
        }
        return true;
    }


    /*
     * Validate input
     */
    bool wxCvResizeDialog::Validate() {
        return true;
    }
}