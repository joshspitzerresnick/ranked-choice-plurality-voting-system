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
  explicit BallotFileProcessor();
  /**
  * @brief Deconstructs a ballot file processor.
  */
  int ProcessFiles(std::list<std::string>, VotingInfo*);
  /**
   * @brief Check if ballot file is valid.
   * 
   * @param[in] int for the algorithm used.  0 is a plurality election, 1 is an stv election.
   * 
   * @param[in] int for the number of candidates in the election.
   * 
   * @param[in] pointer to a ballot object 
   * 
   * @return bool, True if the ballot is invalid, False if the ballot valid. 
   */
  bool IsInvalid(int, int, Ballot*);
  int GetUserInput();
  std::list<std::string> GetFiles(int choice);

 private:
  int ReadFile(std::string fileName, VotingInfo* votinginfo, int* ballotNum);
};
#endif  // SRC_BALLOT_FILE_PROCESSOR_H_