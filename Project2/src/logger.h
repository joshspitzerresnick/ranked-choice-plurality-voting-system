/**
 * @file logger.h
 *
 * @copyright 2020 5801 Team3, based on a singleton logger example, All rights reserved.
 */

#ifndef Logger_H
#define Logger_H
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <list>
#include <string.h>
#include "candidate.h"
using namespace std;
extern char LogFileName[];
#define LOGGER Logger::GetLogger()
/**
*   @brief Singleton Logger Class.
*/
class Logger {
 public:
    /**
    *   @brief Logs a message
    *   @param msg message to be logged.
    */
    void Log(const std::string& msg);
    /**
    *   @brief Function to create the instance of logger class.
    *   @return singleton object of logger class..
    */
    static Logger* GetLogger();
    /**
    *   @brief Logs a list of integers
    *   @param list to be logged.
    */
    void Log(std::list<int> &L);
    /**
    *   @brief Logs a list of Candidate objects
    *   @param list to be logged.
    */
    void Log(std::list<Candidate*> L);
    /**
    *   @brief Logs a list of Ballot objects
    *   @param list to be logged.
    */
    void Log(std::list<Ballot*> L);

 private:
    /**
    *   @brief Default constructor for the Logger class.
    */
    Logger();
    /**
    *   @brief copy constructor for the Logger class.
    */
    Logger(const Logger&) {}  // copy constructor is private
    /**
    *   @brief assignment operator for the Logger class.
    */
    Logger& operator=(const Logger&) { return *this; }
    /**
    *   @brief Log file name.
    **/
   //  static std::string fileName;
    /**
    *   @brief Singleton logger class object pointer.
    **/
    static Logger* pThis;
    /**
    *   @brief Log file stream object.
    **/
    static std::ofstream logFile;
};
#endif  // LOGGER_H_
