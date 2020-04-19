/**
 * @file ballot_file_processor.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <string>
#include <sstream>
#include <vector>
#include <list>
#include "logger.h"

using std::vector;
using std::string;
using std::stringstream;
using std::ios;

Logger::Logger() {
    string e_message;
    log_stream_.open(log_file_.c_str(), std::ios_base::app);
    if (!log_stream_.good()) {
        log_stream_.close();
        std::ostringstream oss;
        oss << "Audit file: " << log_file_ << " alread exists!" << '\n';
        e_message = oss.str();
        throw e_message;
    }
}

Logger::~Logger() {
    log_stream_.close();
}

string Logger::GetLogFile() {
    return log_file_;
}

void Logger::LogToFile(string message) {
    log_stream_ << message << '\n';
}
