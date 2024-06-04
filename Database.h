#ifndef DATABASE_H
#define DATABASE_H

#include "Student.h"
#include <sqlite3.h>
#include <vector>
#include <string>

class Database {
public:
    Database(const std::string& dbPath);
    ~Database();
    void createTable();
    void insertStudent(const Student& student);
    std::vector<Student> queryStudents();
    void clearTable(); 

private:
    sqlite3* db;
};

#endif // DATABASE_H
