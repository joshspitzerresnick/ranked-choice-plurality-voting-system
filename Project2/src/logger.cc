/**
 * @file logger.cc
 *
 * @copyright 2020 5801 Team3, based on a singleton logger example, All rights reserved.
 */
#include "logger.h"
#include <iostream>

const char Logger::fileName[] = "VotingSystemAuditFile.txt";
Logger* Logger::pThis = NULL;
std::ofstream Logger::logFile;
Logger::Logger() {
}
Logger* Logger::GetLogger() {
    if (pThis == NULL) {
        pThis = new Logger();
        logFile.open(fileName, std::ios::out | std::ios::app);
    }
    return pThis;
}
void Logger::Log(const std::string& msg) {
  if (logFile.is_open()) {
    logFile << msg << "\n";
    logFile.flush();
  }
}

