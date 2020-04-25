/**
 * @file stv_election.h
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#ifndef SRC_STV_ELECTION_H_
#define SRC_STV_ELECTION_H_

#include "voting_info.h"
#include "stv_election_record.h"
#include "candidate.h"
#include "ballot.h"
#include <list>
#include <cmath>
#include <iostream>
#include "logger.h"
#include <cstdlib>
#include <string.h>

extern bool BallotShuffleOff;
extern char InvalidBallotFileName[];
extern char LogFileName[];

/**
 * @brief The main class for stv election.
 *
 * Is an stvelection.
 */
class STVElection{
 public:
  /**
  * @brief Constructs an stvelection object to be used in an election.
  *
  * @param[in] VotingInfo* data structure
  *
  */
  explicit STVElection(VotingInfo*);
  /**
  * @brief Run an STV election.
  *
  * @param[in] VotingInfo*, used in result display
  *
  * @return void
  *
  */
  void RunElection(VotingInfo*);
    /**
  * @brief Display STV election results.
  *
  * @param[in] VotingInfo*, a pointer to a VotingInfo object
  * @return void
  *
  */
  void DisplayResult(VotingInfo*);
 private:
  STVElectionRecord* stvElectionRecord_;  // stv election record object
  // STVResultDisplay* stvResultDisplay_;  // stv result display object // NO LONGER USING - Josh
  int numSeats_;  // number of seats to be filled
};
#endif
