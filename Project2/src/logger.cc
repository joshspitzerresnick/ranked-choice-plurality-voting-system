/**
 * @file logger.cc
 *
 * @copyright 2020 5801 Team3, based on a singleton logger example, All rights reserved.
 */
#include "logger.h"

// std::string Logger::fileName = LogFileName;
Logger* Logger::pThis = NULL;
std::ofstream Logger::logFile;
Logger::Logger() {
}
Logger* Logger::GetLogger() {
    if (pThis == NULL) {
        pThis = new Logger();
        logFile.open(LogFileName, std::ios::out | std::ios::app);
    }
    return pThis;
}
void Logger::Log(const std::string& msg) {
  if (logFile.is_open()) {
    logFile << msg << "\n";
    logFile.flush();
  }
}

void Logger::Log(std::list<int> &L) {
  char msg[1000], temp[50];
  snprintf(msg, sizeof(msg), "... ");
  std::list<int>::iterator it;  // Create an iterator of std::list
  int cnt = 0, n = 0;
  for (it= L.begin(); it!= L.end(); it++) {
    n = snprintf(temp, sizeof(temp), "%d,", *it);
    cnt += n;
    if (cnt < 200) {
      strncat(msg, temp, sizeof(msg));
    } else {
      cnt = 0;
      LOGGER->Log(msg);  // Log
      snprintf(msg, sizeof(msg), "...");
      strncat(msg, temp, sizeof(msg));
    }
  }
  logFile << msg << "\n";
  logFile.flush();
}

void Logger::Log(std::list<Candidate*> L) {
  char msg[1000], temp[50];
  snprintf(msg, sizeof(msg), "... ");
  std::list<Candidate*>::iterator it;  // Create an iterator of std::list
  int cnt = 0, n = 0;
  for (it= L.begin(); it!= L.end(); it++) {
    cnt++;
    n = snprintf(temp, sizeof(temp), "%d-%s,", (*it)->GetID(), (*it)->GetName().c_str());
    cnt += n;
    if (cnt < 200) {
      strncat(msg, temp, sizeof(msg));
    } else {
      cnt = 0;
      LOGGER->Log(msg);  // Log
      snprintf(msg, sizeof(msg), "...");
      strncat(msg, temp, sizeof(msg));
    }
  }
  logFile << msg << "\n";
  logFile.flush();
}

void Logger::Log(std::list<Ballot*> L) {
  char msg[1000], temp[50];
  snprintf(msg, sizeof(msg), "... ");
  std::list<Ballot*>::iterator it;  // Create an iterator of std::list
  int cnt = 0, n = 0;
  for (it= L.begin(); it!= L.end(); it++) {
    n = snprintf(temp, sizeof(temp), "%d,", (*it)->GetID());
    cnt += n;
    if (cnt < 200) {
      strncat(msg, temp, sizeof(msg));
    } else {
      cnt = 0;
      LOGGER->Log(msg);  // Log
      snprintf(msg, sizeof(msg), "...");
      strncat(msg, temp, sizeof(msg));
    }
  }
  logFile << msg << "\n";
  logFile.flush();
}
