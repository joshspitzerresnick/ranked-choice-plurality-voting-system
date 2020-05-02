/**
 * @file ballot.h
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#ifndef SRC_BALLOT_H_
#define SRC_BALLOT_H_

#include <iostream>
#include <string>
#include <list>

/**
 * @brief The main class for ballots.
 *
 * Is a ballot.
 */
class Ballot {  // : public Reporter {
 public:
  /**
  * @brief Constructs a ballot with a ranked candidate list and id
  *
  *
  * @param[in] int holding a ballot id number
  * @param[in] linked list containing candidate id numbers
  * @param[in] linked list containing original ballot
  *
  */
  explicit Ballot(int, std::list<int>, std::list<int>);
  /**
  * @brief Get ballot id
  * @return ballot id
  */
  int GetID();
  /**
  * @brief Get the ranked candidate id list
  * @return std::list<int> ranked candidate ID List
  */
  std::list<int> GetRankedCandidateIDList();
  /**
  * @brief Get the original ballot
  * @return std::list<int> original ballot
  */
  std::list<int> GetOriBallot();
 private:
  std::list<int> rankedCandidateIDList_;  // list of candidates
  std::list<int> oriBallot_; 
  int id_;  // ballot id number
};
#endif  // SRC_BALLOT_H_
