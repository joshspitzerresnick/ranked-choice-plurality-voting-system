/**
 * @file ballot_file_processor.h
 *
 * @copyright 2020 Josh Spitzer-Resnick, spitz123
 */

#ifndef SRC_BALLOT_FILE_PROCESSOR_H_
#define SRC_BALLOT_FILE_PROCESSOR_H_

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <cctype>
#include <iostream>
#include "logger.h"
#include <dirent.h>
#include <sys/types.h>
#include "candidate.h"
#include "ballot.h"
#include "voting_info.h"

// #define INVALIDATED_FILE "InvalidBallotFile.txt"
extern char InvalidBallotFileName[];

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
  * @param[in] void
  */
  BallotFileProcessor();
  /**
   * @brief Process ballot files, return total number of ballots read.
   * 
   * @param[in] std::list<std::string> Ballot file list.
   * 
   * @param[in] VotingInfo* VotingInfo object to store information from ballots.
   * 
   * @return int, total number of ballots processed. 
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
  /**
   * @brief Get user's input on how they want to provide ballot files.
   * 
   * @param[in] void.
   * 
   * @return int, user's choice. 
   */
  int GetUserInput();
  /**
   * @brief Fetch files based on user's option choice.
   * 
   * @param[in] int, user's choice: 1-type in files' names; 2-type in directory name where the files are located.
   * 
   * @return list<string>, file name list. 
   */
  std::list<std::string> GetFiles(int choice);

 private:
  /**
   * @brief Process a ballot file, return number of ballots read.
   * 
   * @param[in] string, Ballot file name.
   * 
   * @param[in] VotingInfo* VotingInfo object to store information from ballots.
   *
   * @param[in] int* ballot index for ballot ID assignment.
   * 
   * @return int, number of ballots processed. 
   */
  int ReadFile(std::string fileName, VotingInfo* votinginfo, int* ballotNum);
};
#endif  // SRC_BALLOT_FILE_PROCESSOR_H_