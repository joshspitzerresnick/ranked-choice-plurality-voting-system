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

extern bool BallotShuffleOff;

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
  explicit STVElection();
  /**
  * @brief Run an STV election.
  *
  * @param[in] none
  * @return void
  *
  */
  void RunElection(VotingInfo*, bool);
    /**
  * @brief Display STV election results.
  *
  * @param[in] none, using member structure within the same class
  * @return void
  *
  */
  void DisplayResult(STVElectionRecord*, VotingInfo*);
};
#endif
