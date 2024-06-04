#include "Database.h"
#include <iostream>

Database::Database(const std::string& dbPath) {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
    else {
        std::cout << "Opened database successfully" << std::endl;
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

void Database::createTable() {
    if (!db) return;

    char* errMsg = 0;
    const char* sql = "CREATE TABLE IF NOT EXISTS STUDENT("
        "ID INT PRIMARY KEY NOT NULL,"
        "SURNAME TEXT NOT NULL,"
        "NAME TEXT NOT NULL,"
        "BIRTHDATE TEXT NOT NULL,"
        "PHONE TEXT NOT NULL,"
        "FACULTY TEXT NOT NULL,"
        "COURSE INT NOT NULL,"
        "GROUPNAME TEXT NOT NULL);";

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "Table created successfully" << std::endl;
    }
}

void Database::insertStudent(const Student& student) {
    if (!db) return;

    char* errMsg = 0;
    std::string sql = "INSERT INTO STUDENT (ID, SURNAME, NAME, BIRTHDATE, PHONE, FACULTY, COURSE, GROUPNAME) VALUES ("
        + std::to_string(student.getId()) + ", '"
        + student.getSurname() + "', '"
        + student.getName() + "', '"
        + student.getBirthDate() + "', '"
        + student.getPhone() + "', '"
        + student.getFaculty() + "', "
        + std::to_string(student.getCourse()) + ", '"
        + student.getGroup() + "');";

    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "Record created successfully" << std::endl;
    }
}

std::vector<Student> Database::queryStudents() {
    std::vector<Student> students;
    if (!db) return students;

    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM STUDENT";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
        return students;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string surname(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        std::string birthdate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        std::string phone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        std::string faculty(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        int course = sqlite3_column_int(stmt, 6);
        std::string group(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));

        students.push_back(Student(id, surname, name, birthdate, phone, faculty, course, group));
    }

    sqlite3_finalize(stmt);
    return students;
}
