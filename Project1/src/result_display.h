/**
 * @file result_display.h
 *
 * @copyright 2020 Josh Spitzer-Resnick, spitz123
 */

#ifndef SRC_RESULT_DISPLAY_H_
#define SRC_RESULT_DISPLAY_H_

#include <iostream>
#include <string>

#include "election_record.h"
#include "voting_info.h"

/**
 * @brief The main class for displaying election results.
 *
 * Displays election results.
 */
class ResultDisplay {
 public:
  /**
  * @brief Constructs a container for displaying election results.
  */
  explicit ResultDisplay();
  /**
  * @brief Deconstructs a container for displaying election results.
  */
  ~ResultDisplay();
  /**
  * @brief Displays election results.
  *
  * @param[in] ElectionRecord* holding election results.
  * @param[in] VotingInfo* holding voting information.
  */
  virtual void DisplayElectionResults(ElectionRecord*, VotingInfo*) = 0;
};
#endif  // SRC_RESULT_DISPLAY_H_
