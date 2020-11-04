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
    const wxString wxCvResizeDialog::RESIZE_UNIT_CHOICES[] = {"px", "%"};

    wxCvResizeDialog::wxCvResizeDialog(wxWindow* parent, const cv::Mat& image) : wxDialog(parent, wxID_ANY,
                                                                                          wxT("Redimensionar imagem"),
                                                                                          wxDefaultPosition,
                                                                                          wxDefaultSize,
                                                                                          wxDEFAULT_DIALOG_STYLE) {
        imageWidth = image.size().width;
        imageHeight = image.size().height;

        interpolation = new wxChoice(this, ID_INTERPOLATION);
        for (auto& choice : INTERPOLATION_CHOICES) {
            interpolation->Append(choice);
        }
        interpolation->SetSelection(0);

        unit = new wxChoice(this, ID_UNIT);
        for (auto& choice : RESIZE_UNIT_CHOICES) {
            unit->Append(choice);
        }
        unit->SetSelection(Pixel);

        x = new wxTextCtrl(this, ID_X, std::to_string(image.size().width));
        y = new wxTextCtrl(this, ID_Y, std::to_string(image.size().width));

        wxFlexGridSizer* flexGrid = new wxFlexGridSizer(2, wxSize(5, 5));
        flexGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Interpolação")));
        flexGrid->Add(interpolation, 1, wxEXPAND);
        flexGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Unidade")));
        flexGrid->Add(unit, 1, wxEXPAND);
        flexGrid->Add(new wxStaticText(this, wxID_ANY, wxT("x")));
        flexGrid->Add(x, 1, wxEXPAND);
        flexGrid->Add(new wxStaticText(this, wxID_ANY, wxT("y")));
        flexGrid->Add(y, 1, wxEXPAND);

        wxBoxSizer* box = new wxBoxSizer(wxVERTICAL);
        box->Add(flexGrid, 1, wxEXPAND | wxALL, 5);
        box->Add(wxDialog::CreateButtonSizer(wxOK | wxCANCEL), 0, wxALIGN_CENTER | wxBOTTOM, 5);

        SetSizer(box);
        Layout();
        Fit();
        Center();

        Bind(wxEVT_COMBOBOX, &wxCvResizeDialog::OnUnitChanged, this, ID_UNIT);
    }


    /*
     * Resize @image according to the dimensions/proportions specified by the user
     */
    bool wxCvResizeDialog::Apply(cv::Mat& image) {
        if (Validate()) {
            int interpolationIndex = cv::INTER_LINEAR + interpolation->GetSelection();
            if (unit->GetSelection() == Pixel) {
                long w, h;
                x->GetValue().ToLong(&w);
                y->GetValue().ToLong(&h);
                cv::resize(image, image, cv::Size(w, h), 0.0, 0.0, interpolationIndex);
            }
            else if (unit->GetSelection() == Percentage) {
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


    /*
     * Convert the x and y values between px and % units when the unit combobox changes
     */
    void wxCvResizeDialog::OnUnitChanged(wxCommandEvent& event) {
        std::cout << "AQUI" << std::endl;

        switch (unit->GetSelection()) {
            case Pixel: {
                double sx, sy;
                x->GetValue().ToDouble(&sx);
                y->GetValue().ToDouble(&sy);
                x->ChangeValue(std::to_string(sx * imageWidth));
                y->ChangeValue(std::to_string(sy * imageHeight));

                std::cout << sx * imageWidth << " " << sy * imageHeight;
                break;
            }
            case Percentage: {
                long w, h;
                x->GetValue().ToLong(&w);
                y->GetValue().ToLong(&h);
                x->ChangeValue(std::to_string((float) w / imageWidth));
                y->ChangeValue(std::to_string((float) h / imageHeight));

                std::cout << (float) w / imageWidth << " " << (float) h / imageHeight;
                break;
            }
        }
    }
}