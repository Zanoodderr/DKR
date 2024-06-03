#pragma once

#include <iostream>
#include <string>
#include <sstream>



class Student {
private:
    int id;
    std::string surname;
    std::string name;
    std::string birthDate;
    std::string phone;
    std::string faculty;
    int course;
    std::string group;

public:

    Student() : id(0), course(0) {}
    Student(int id, std::string surname, std::string name, std::string birthDate, std::string phone, std::string faculty, int course, std::string group)
        : id(id), surname(surname), name(name), birthDate(birthDate), phone(phone), faculty(faculty), course(course), group(group) {}


    void setId(int id) { this->id = id; }
    void setSurname(const std::string& surname) { this->surname = surname; }
    void setName(const std::string& name) { this->name = name; }
    void setBirthDate(const std::string& birthDate) { this->birthDate = birthDate; }
    void setPhone(const std::string& phone) { this->phone = phone; }
    void setFaculty(const std::string& faculty) { this->faculty = faculty; }
    void setCourse(int course) { this->course = course; }
    void setGroup(const std::string& group) { this->group = group; }


    int getId() const { return id; }
    std::string getSurname() const { return surname; }
    std::string getName() const { return name; }
    std::string getBirthDate() const { return birthDate; }
    std::string getPhone() const { return phone; }
    std::string getFaculty() const { return faculty; }
    int getCourse() const { return course; }
    std::string getGroup() const { return group; }


    std::string toString() const {
        std::ostringstream oss;
        oss << "ID: " << id << ", Surname: " << surname << ", Name: " << name
            << ", BirthDate: " << birthDate << ", Phone: " << phone
            << ", Faculty: " << faculty << ", Course: " << course
            << ", Group: " << group;
        return oss.str();
    }


    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << student.toString();
        return os;
    }
};

