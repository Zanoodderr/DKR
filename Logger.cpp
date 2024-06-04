#include "Logger.h"

Logger::Logger(const std::string& filename) {
    logFile.open(filename, std::ios_base::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Unable to open log file");
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string& message) {
    if (logFile.is_open()) {
        logFile << message << std::endl;
    }
}
