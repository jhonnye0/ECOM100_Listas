//
// Created by Valerio Nogueira on 03/11/2020.
//

#include "wxCV.h"
#include <wx/menu.h>
#include <wx/filedlg.h>
#include <wx/stdpaths.h>
#include "wxCvResizeDialog.h"


namespace wxcv {
    /*
     * Create a MainWindow and show it
     */
    bool wxCV::OnInit() {
        MainWindow* mainWindow = new MainWindow();
        mainWindow->Show(true);
        return true;
    }

    MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "wxCV") {
        InitMenu();
        BindEvents();
        Center();
    }

    /*
     * Create the menu bar and attach it to the window
     */
    void MainWindow::InitMenu() {
        wxMenuBar* bar = new wxMenuBar();
        wxMenu* file = new wxMenu();
        wxMenu* edit = new wxMenu();
        // wxMenu* view = new wxMenu();
        wxMenu* tools = new wxMenu();
        wxMenu* help = new wxMenu();

        // File
        file->Append(ID_OPEN_IMAGE, wxT("&Abrir...\tCtrl+O"));
        file->Append(ID_SAVE_IMAGE, wxT("&Salvar...\tCtrl+S"));
        file->AppendSeparator();
        file->Append(wxID_EXIT, "&Sair");
        // Edit
        edit->Append(ID_RESIZE_IMAGE, wxT("Redimensionar"));
        // View
        // Tools
        tools->Append(ID_FILTER_2D, wxT("&Filtro 2D...\tCtrl+F"));
        // Help
        help->Append(wxID_ABOUT, "Sobre");

        bar->Append(file, wxT("Arquivo"));
        bar->Append(edit, wxT("Editar"));
        // bar->Append(view, wxT("Exibir"));
        bar->Append(tools, wxT("Ferramentas"));
        bar->Append(help, wxT("Ajuda"));

        SetMenuBar(bar);
        CreateStatusBar();
    }

    /*
     * Bind each menu bar item
     */
    void MainWindow::BindEvents() {
        Bind(wxEVT_MENU, &MainWindow::OpenImage, this, ID_OPEN_IMAGE);
        Bind(wxEVT_MENU, &MainWindow::SaveImage, this, ID_SAVE_IMAGE);
        Bind(wxEVT_MENU, &MainWindow::Exit, this, wxID_EXIT);
        Bind(wxEVT_MENU, &MainWindow::ResizeImage, this, ID_RESIZE_IMAGE);
        Bind(wxEVT_MENU, &MainWindow::Filter2D, this, ID_FILTER_2D);
        Bind(wxEVT_MENU, &MainWindow::About, this, wxID_ABOUT);
    }


    /*
     * Prompt the user to choose an image from the file explorer and load it into @image with OpenCV
     */
    void MainWindow::OpenImage(wxCommandEvent& event) {
        wxFileDialog fileDialog(this, wxT("Abrir imagem"));

        if (fileDialog.ShowModal() == wxID_CANCEL) {
            return;
        }

        image = cv::imread(fileDialog.GetPath().ToStdString());
        if (!image.empty()) {
            SetStatusText(fileDialog.GetFilename() + wxT(" carregada com sucesso!"));
        }
    }


    /*
     * Prompt the user to save the image in disk using OpenCV
     */
    void MainWindow::SaveImage(wxCommandEvent& event) {
        wxFileDialog fileDialog(this, wxT("Salvar imagem"));

        if (fileDialog.ShowModal() == wxID_CANCEL) {
            return;
        }

        cv::imwrite(fileDialog.GetPath().ToStdString(), image);
        SetStatusText(fileDialog.GetFilename() + wxT(" salvo com sucesso!"));
    }


    /*
     * Quit the application
     */
    void MainWindow::Exit(wxCommandEvent& event) {
        Close(true);
    }


    /*
     * Show a wxCvResizeDialog and resize @image to the desired size
     */
    void MainWindow::ResizeImage(wxCommandEvent& event) {
        wxCvResizeDialog resizeDialog(this, image);

        if (resizeDialog.ShowModal() == wxID_OK) {
            resizeDialog.Apply(image);
            std::cout << image.size() << std::endl;
        }
    }

    void MainWindow::Filter2D(wxCommandEvent& event) {

    }

    void MainWindow::About(wxCommandEvent& event) {

    }

    wxIMPLEMENT_APP(wxCV);
}
