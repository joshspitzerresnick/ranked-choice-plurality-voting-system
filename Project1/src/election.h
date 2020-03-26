/**
 * @file election.h
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#ifndef SRC_ELECTION_H_
#define SRC_ELECTION_H_

#include <iostream>
#include <string>
#include <list>
#include "src/voting_info.h"

/**
 * @brief The main class for elections.
 *
 * Abstract class for an election.
 */
class AbstractElection {  // : public Reporter {
 public:
  /**
  * @brief Constructs an abstract class to run an election.
  */
  AbstractElection();
  /**
  * @brief Virtual RunElection method.
  */
  virtual void RunElection(VotingInfo*);

 private:
  /*
  * Add ElectionRecord and ResultDisplay - what are these?
  */
};
/**
 * @brief The main class for Plurality Elections.
 *
 * Runs a plurality election
 */
class PluralityElection : public AbstractElection {
 public:
    /**
  * @brief Constructs a Plurality Election type of election to run.
  */
  PluralityElection();
  /**
  * @brief Runs a plurality election.
  */
  void RunElection(VotingInfo*);
};
/**
 * @brief The main class for STV Elections.
 *
 * Runs an stv election
 */
class STVElection : public AbstractElection {
 public:
    /**
  * @brief Constructs an STV Election type of election to run.
  */
  STVElection();
  /**
  * @brief Runs an stv election.
  */
  void RunElection(VotingInfo*);
};
#endif  // SRC_ELECTION_H_
