#include <wx/wx.h>
#include "Student.h"
#include "Database.h"
#include "Logger.h"
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

    void OnFilterByFaculty(wxCommandEvent& event);
    void OnFilterByFacultyAndCourse(wxCommandEvent& event);
    void OnFilterByBirthDate(wxCommandEvent& event);
    void OnFilterByGroup(wxCommandEvent& event);
    void OnFilterShowAll(wxCommandEvent& event);
    void OnAddStudent(wxCommandEvent& event);

    void FilterStudentsByFaculty(const std::string& faculty);
    void FilterStudentsByFacultyAndCourse();
    void FilterStudentsByBirthDate(const std::string& birthDate);
    void FilterStudentsByGroup(const std::string& group);
    void FilterShowAll(const std::string& all);

    wxListBox* studentList;
    wxTextCtrl* inputSurname;
    wxTextCtrl* inputName;
    wxTextCtrl* inputBirthDate;
    wxTextCtrl* inputPhone;
    wxTextCtrl* inputFaculty;
    wxTextCtrl* inputCourse;
    wxTextCtrl* inputGroup;

    Database db;
    Logger logger;
    std::vector<Student> students;

    void LoadStudents();
    void RefreshStudentList();
};

enum {
    ID_Hello = 1,
    ID_AddStudent = 2,
    ID_FilterByFaculty = 3,
    ID_FilterByFacultyAndCourse = 4,
    ID_FilterByBirthDate = 5,
    ID_FilterByGroup = 6,
    ID_FilterShowAll = 7
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("Student Management");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title), db("DKR.db"), logger("app.log") {

    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Info...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenu* menuFilter = new wxMenu;
    menuFilter->Append(ID_FilterByFaculty, "By &Faculty...\tCtrl-F", "Filter students by faculty");
    menuFilter->Append(ID_FilterByFacultyAndCourse, "By &Faculty and Course...\tCtrl-C", "Filter students by faculty and course");
    menuFilter->Append(ID_FilterByBirthDate, "By &Birth Date...\tCtrl-B", "Filter students by birth date");
    menuFilter->Append(ID_FilterByGroup, "By &Group...\tCtrl-G", "Filter students by group");
    menuFilter->Append(ID_FilterShowAll, "Show &All...\tCtrl-A", "Show all students");

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuFilter, "&Filter");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to Student Manager!");

    wxPanel* panel = new wxPanel(this, -1);

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    studentList = new wxListBox(panel, wxID_ANY);
    vbox->Add(studentList, 1, wxEXPAND | wxALL, 10);

    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    hbox1->Add(new wxStaticText(panel, wxID_ANY, wxT("Surname")), 0, wxRIGHT, 8);
    inputSurname = new wxTextCtrl(panel, wxID_ANY);
    hbox1->Add(inputSurname, 1);
    vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
    hbox2->Add(new wxStaticText(panel, wxID_ANY, wxT("Name")), 0, wxRIGHT, 8);
    inputName = new wxTextCtrl(panel, wxID_ANY);
    hbox2->Add(inputName, 1);
    vbox->Add(hbox2, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
    hbox3->Add(new wxStaticText(panel, wxID_ANY, wxT("Birth Date")), 0, wxRIGHT, 8);
    inputBirthDate = new wxTextCtrl(panel, wxID_ANY);
    hbox3->Add(inputBirthDate, 1);
    vbox->Add(hbox3, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    wxBoxSizer* hbox4 = new wxBoxSizer(wxHORIZONTAL);
    hbox4->Add(new wxStaticText(panel, wxID_ANY, wxT("Phone")), 0, wxRIGHT, 8);
    inputPhone = new wxTextCtrl(panel, wxID_ANY);
    hbox4->Add(inputPhone, 1);
    vbox->Add(hbox4, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    wxBoxSizer* hbox5 = new wxBoxSizer(wxHORIZONTAL);
    hbox5->Add(new wxStaticText(panel, wxID_ANY, wxT("Faculty")), 0, wxRIGHT, 8);
    inputFaculty = new wxTextCtrl(panel, wxID_ANY);
    hbox5->Add(inputFaculty, 1);
    vbox->Add(hbox5, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    wxBoxSizer* hbox6 = new wxBoxSizer(wxHORIZONTAL);
    hbox6->Add(new wxStaticText(panel, wxID_ANY, wxT("Course")), 0, wxRIGHT, 8);
    inputCourse = new wxTextCtrl(panel, wxID_ANY);
    hbox6->Add(inputCourse, 1);
    vbox->Add(hbox6, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    wxBoxSizer* hbox7 = new wxBoxSizer(wxHORIZONTAL);
    hbox7->Add(new wxStaticText(panel, wxID_ANY, wxT("Group")), 0, wxRIGHT, 8);
    inputGroup = new wxTextCtrl(panel, wxID_ANY);
    hbox7->Add(inputGroup, 1);
    vbox->Add(hbox7, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    wxButton* btnAdd = new wxButton(panel, ID_AddStudent, wxT("Add Student"));
    vbox->Add(btnAdd, 0, wxALIGN_CENTER | wxALL, 10);

    panel->SetSizer(vbox);

    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnFilterByFaculty, this, ID_FilterByFaculty);
    Bind(wxEVT_MENU, &MyFrame::OnFilterByFacultyAndCourse, this, ID_FilterByFacultyAndCourse);
    Bind(wxEVT_MENU, &MyFrame::OnFilterByBirthDate, this, ID_FilterByBirthDate);
    Bind(wxEVT_MENU, &MyFrame::OnFilterByGroup, this, ID_FilterByGroup);
    Bind(wxEVT_MENU, &MyFrame::OnFilterShowAll, this, ID_FilterShowAll);
    Bind(wxEVT_BUTTON, &MyFrame::OnAddStudent, this, ID_AddStudent);

    db.createTable();
    LoadStudents();
}

void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnAddStudent(wxCommandEvent& event) {
    int id = students.size() + 1;
    std::string surname = inputSurname->GetValue().ToStdString();
    std::string name = inputName->GetValue().ToStdString();
    std::string birthDate = inputBirthDate->GetValue().ToStdString();
    std::string phone = inputPhone->GetValue().ToStdString();
    std::string faculty = inputFaculty->GetValue().ToStdString();
    int course = std::stoi(inputCourse->GetValue().ToStdString());
    std::string group = inputGroup->GetValue().ToStdString();

    Student newStudent(id, surname, name, birthDate, phone, faculty, course, group);
    db.insertStudent(newStudent);

    logger.log("Student added: " + newStudent.toString());

    LoadStudents(); // 
}

void MyFrame::LoadStudents() {
    students = db.queryStudents();

    logger.log("Students loaded: " + std::to_string(students.size()));

    RefreshStudentList();
}

void MyFrame::RefreshStudentList() {
    studentList->Clear();
    for (const auto& student : students) {
        studentList->Append(wxString::FromUTF8(student.toString().c_str()));
    }

    logger.log("Student list refreshed.");
}

void MyFrame::OnFilterByFaculty(wxCommandEvent& event) {
    wxTextEntryDialog dialog(this, "Enter Faculty:", "Filter by Faculty");
    if (dialog.ShowModal() == wxID_OK) {
        std::string faculty = dialog.GetValue().ToStdString();
        FilterStudentsByFaculty(faculty);
    }
}

void MyFrame::OnFilterByFacultyAndCourse(wxCommandEvent& event) {
    FilterStudentsByFacultyAndCourse();
}

void MyFrame::OnFilterByBirthDate(wxCommandEvent& event) {
    wxTextEntryDialog dialog(this, "Enter Birth Date (YYYY-MM-DD):", "Filter by Birth Date");
    if (dialog.ShowModal() == wxID_OK) {
        std::string birthDate = dialog.GetValue().ToStdString();
        FilterStudentsByBirthDate(birthDate);
    }
}

void MyFrame::OnFilterByGroup(wxCommandEvent& event) {
    wxTextEntryDialog dialog(this, "Enter Group:", "Filter by Group");
    if (dialog.ShowModal() == wxID_OK) {
        std::string group = dialog.GetValue().ToStdString();
        FilterStudentsByGroup(group);
    }
}

void MyFrame::OnFilterShowAll(wxCommandEvent& event) {
    studentList->Clear();
    for (const auto& student : students) {
        studentList->Append(wxString::FromUTF8(student.toString().c_str()));
    }
    logger.log("Showed all. ");
}

void MyFrame::FilterStudentsByFaculty(const std::string& faculty) {
    studentList->Clear();
    for (const auto& student : students) {
        if (student.getFaculty() == faculty) {
            studentList->Append(wxString::FromUTF8(student.toString().c_str()));
        }
    }
    logger.log("Filtered by faculty: " + faculty);
}

void MyFrame::FilterStudentsByFacultyAndCourse() {
    wxTextEntryDialog facultyDialog(this, "Enter Faculty:", "Filter by Faculty and Course");
    if (facultyDialog.ShowModal() == wxID_OK) {
        std::string faculty = facultyDialog.GetValue().ToStdString();

        wxTextEntryDialog courseDialog(this, "Enter Course:", "Filter by Faculty and Course");
        if (courseDialog.ShowModal() == wxID_OK) {
            int course = std::stoi(courseDialog.GetValue().ToStdString());

            studentList->Clear();
            for (const auto& student : students) {
                if (student.getFaculty() == faculty && student.getCourse() == course) {
                    studentList->Append(wxString::FromUTF8(student.toString().c_str()));
                }
            }
            logger.log("Filtered by faculty: " + faculty + " and course: " + std::to_string(course));
        }
    }
}

void MyFrame::FilterStudentsByBirthDate(const std::string& birthDate) {
    studentList->Clear();
    for (const auto& student : students) {
        if (student.getBirthDate() > birthDate) {
            studentList->Append(wxString::FromUTF8(student.toString().c_str()));
        }
    }
    logger.log("Filtered by birth date: " + birthDate);
}

void MyFrame::FilterStudentsByGroup(const std::string& group) {
    studentList->Clear();
    for (const auto& student : students) {
        if (student.getGroup() == group) {
            studentList->Append(wxString::FromUTF8(student.toString().c_str()));
        }
    }
    logger.log("Filtered by group: " + group);
}

void MyFrame::FilterShowAll(const std::string& all) {
    studentList->Clear();
    for (const auto& student : students) {
        studentList->Append(wxString::FromUTF8(student.toString().c_str()));
    }
    logger.log("Showed all: ");
}