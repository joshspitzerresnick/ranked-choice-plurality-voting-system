/**
 * @file ballot_file_processor.h
 *
 * @copyright 2020 Josh Spitzer-Resnick, spitz123
 */

#ifndef SRC_BALLOT_FILE_PROCESSOR_H_
#define SRC_BALLOT_FILE_PROCESSOR_H_

#include <iostream>
#include <fstream>
#include <string>

#include "voting_info.h"

/**
 * @brief The main class for processing ballot files.
 *
 * Is a ballot file processor.
 */
class BallotFileProcessor {
 public:
  /**
  * @brief Constructs a ballot file processor with standard empty string.
  *
  * @param[in] string holding text of a csv ballot file.
  */
  explicit BallotFileProcessor(std::string = "");
  /**
  * @brief Deconstructs a ballot file processor.
  */
  ~BallotFileProcessor();
  /**
  * @brief Processes ballot files.
  *
  * @param[in] pointer to VotingInfo object with algorithm and seat info.
  */
  void ProcessFiles(VotingInfo*);

 private:
  std::string ballot_file_name_;  // Name of the ballot file to process.
  std::ifstream ballot_files_;  // Stream to use for processing ballot file.
};
#endif  // SRC_BALLOT_FILE_PROCESSOR_H_
