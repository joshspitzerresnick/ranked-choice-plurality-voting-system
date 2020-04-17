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
        std::cout << "Construct new Logger obj..." << std::endl;
        pThis = new Logger();
        std::cout << "Open new log file..." << std::endl;
        logFile.open(fileName, std::ios::out | std::ios::app);
    }
    return pThis;
}
void Logger::Log(const std::string& msg) {
    std::cout << "log message to file..." << msg << std::endl;
    logFile << msg << "\n";
}

