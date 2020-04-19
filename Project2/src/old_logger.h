/**
 * @file logger.h
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include <iostream>
#include <fstream>
#include <string>

/**
 * @brief The main class for logging info to an audit file.
 *
 * Is an election file logger
 */
class Logger {
 public:
  /**
  * @brief Constructs an object to use to log election information to a file.
  *
  * @param[in] string holding text of a csv ballot file.
  */
  Logger();
  /**
  * @brief Deconstructs election logging object.
  */
  ~Logger();
  /**
  * @brief Get the file name of the election information audit file.
  */
  std::string GetLogFile();
  /**
  * @brief Send a message to the logger to append to an election information file.
  *
  * @param[in] message to be written to the election information file.
  */
  void LogToFile(std::string message);

 private:
  std::string log_file_ = "audit_file.txt";  // Name of audit file.
  std::ofstream log_stream_;  // Stream to use for appending to the audit file.
};
#endif  // SRC_LOGGER_H_
