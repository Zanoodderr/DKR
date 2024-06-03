#include <wx/wx.h>
#include "Student.h"
#include <vector>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    wxListBox* studentList;
    std::vector<Student> students;

    void LoadStudents();
};

enum {
    ID_Hello = 1
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("Student Management");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title) {

    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    studentList = new wxListBox(this, wxID_ANY);

    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);

    LoadStudents();
}

void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::LoadStudents() {
    students.push_back(Student(1, "Ivanov", "Ivan", "2000-01-01", "123456789", "CS", 1, "A"));
    students.push_back(Student(2, "Petrov", "Petr", "1999-02-01", "987654321", "Math", 2, "B"));

    for (const auto& student : students) {
        studentList->Append(wxString::FromUTF8(student.toString()));
    }
}
