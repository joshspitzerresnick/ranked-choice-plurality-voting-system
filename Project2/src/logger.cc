/**
 * @file logger.cc
 *
 * @copyright 2020 5801 Team3, based on a singleton logger example, All rights reserved.
 */
#include "logger.h"

const char Logger::fileName[] = "audit.txt";
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

void Logger::Log(std::list<int> &L) {
  char msg[1000], temp[50];
  snprintf(msg, sizeof(msg), "... ");
  std::list<int>::iterator it;  // Create an iterator of std::list
  int cnt = 0;
  for (it= L.begin(); it!= L.end(); it++) {
    cnt++;
    snprintf(temp, sizeof(temp), "%d,", *it);
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
  std::string str;
  snprintf(msg, sizeof(msg), "... ");
  std::list<Candidate*>::iterator it;  // Create an iterator of std::list
  int cnt = 0;
  for (it= L.begin(); it!= L.end(); it++) {
    cnt++;
    str = (*it)->GetName();
    snprintf(temp, sizeof(temp), "%s,", str.c_str());
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
  int cnt = 0;
  for (it= L.begin(); it!= L.end(); it++) {
    cnt++;
    snprintf(temp, sizeof(temp), "%d,", (*it)->GetID());
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
