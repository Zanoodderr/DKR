#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include "Student.h"

class Database {
public:
    Database(const std::string& dbPath);
    ~Database();

    void createTable();
    void insertStudent(const Student& student);
    std::vector<Student> queryStudents();

private:
    sqlite3* db;
};

#endif // DATABASE_H
