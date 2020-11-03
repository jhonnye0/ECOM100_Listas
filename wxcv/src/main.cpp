//
// Created by Valerio Nogueira on 03/11/2020.
//

#include "wxCV.h"
#include <wx/menu.h>


namespace wxcv {

    bool wxCV::OnInit() {
        MainWindow* mainWindow = new MainWindow();
        mainWindow->Show(true);
        return true;
    }

    MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "wxCV") {
        InitMenu();
        Center();
    }

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

    wxIMPLEMENT_APP(wxCV);
}
