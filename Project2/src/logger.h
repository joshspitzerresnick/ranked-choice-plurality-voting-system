/**
 * @file logger.h
 *
 * @copyright 2020 5801 Team3, based on a singleton logger example, All rights reserved.
 */

#ifndef Logger_H
#define Logger_H
#include <fstream>
#include <string>
#define LOGGER Logger::GetLogger()
/**
*   Singleton Logger Class.
*/
class Logger {
 public:
    /**
    *   Logs a message
    *   @param msg message to be logged.
    */
    void Log(const std::string& msg);
    /**
    *   Funtion to create the instance of logger class.
    *   @return singleton object of logger class..
    */
    static Logger* GetLogger();

 private:
    /**
    *    Default constructor for the Logger class.
    */
    Logger();
    /**
    *   copy constructor for the Logger class.
    */
    Logger(const Logger&) {}  // copy constructor is private
    /**
    *   assignment operator for the Logger class.
    */
    Logger& operator=(const Logger&) { return *this; }
    /**
    *   Log file name.
    **/
    static const char fileName[];
    /**
    *   Singleton logger class object pointer.
    **/
    static Logger* pThis;
    /**
    *   Log file stream object.
    **/
    static std::ofstream logFile;
};
#endif  // LOGGER_H_
