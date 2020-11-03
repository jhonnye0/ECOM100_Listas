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

    wxCvResizeDialog::wxCvResizeDialog(wxWindow* parent) : wxDialog(parent, wxID_ANY, wxT("Redimensionar imagem")) {
        interpolation = new wxChoice(this, ID_INTERPOLATION);
        for (auto& choice : INTERPOLATION_CHOICES) {
            interpolation->Append(choice);
        }
        interpolation->SetLabel(wxT("Interpolação"));
        interpolation->SetSelection(0);

        resizeMode = new wxChoice(this, ID_RESIZE_MODE);
        for (auto& choice : RESIZE_MODE_CHOICES) {
            resizeMode->Append(choice);
        }
        resizeMode->SetLabel(wxT("Modo"));
        resizeMode->SetSelection(0);

        x = new wxTextCtrl(this, ID_X);
        x->SetLabel(wxT("x"));
        y = new wxTextCtrl(this, ID_Y);
        y->SetLabel(wxT("y"));

        wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
        for(wxWindow* control : {(wxWindow*) interpolation, (wxWindow*) resizeMode, (wxWindow*) x, (wxWindow*) y}){
            wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
            hbox->Add(new wxStaticText(this, wxID_ANY, control->GetLabel()), 1);
            hbox->Add(control, 1);
            vbox->Add(hbox);
        }
        vbox->Add(new wxButton(this, wxID_OK));
        vbox->Layout();

        SetSizer(vbox);
    }


    /*
     * Resize @image according to the dimensions/proportions specified by the user
     */
    bool wxCvResizeDialog::Apply(cv::Mat& image) {
        if (Validate()) {
            std::cout << resizeMode->GetStringSelection() << std::endl;

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