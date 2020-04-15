/**
 * @file plurality_election.h
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#ifndef SRC_PLURALITY_ELECTION_H_
#define SRC_PLURALITY_ELECTION_H_

#include "voting_info.h"
#include "candidate.h"
#include "ballot.h"
#include "plurality_election_record.h"

/**
 * @brief The main class for plurality election.
 *
 * Is an plurality election.
 */
class PluralityElection{
 public:
  /**
  * @brief Constructs an PluralityElection object to be used in an election.
  *
  *
  */
  explicit PluralityElection();
  /**
  * @brief Run a plurality election.
  *
  * @param[in] VotingInfo*, a pointer to a VotingInfo object
  * @return void
  *
  */
  void RunElection(VotingInfo*);

  /**
  * @brief Print plurality election results.
  *
  * @param[in] PluralityElectionRecord*, pointer to an election record.
  * @param[in] VotingInfo*, a pointer to a VotingInfo object
  * @return void
  *
  */
  void DisplayResults(PluralityElectionRecord*, VotingInfo*);
};
#endif