/**
 * @file candidate.h
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#ifndef SRC_CANDIDATE_H_
#define SRC_CANDIDATE_H_

#include <iostream>
#include <string>
#include <list>
#include "ballot.h"

/**
 * @brief The main class for candidates.
 *
 * Is a candidate.
 */
class Candidate {  // : public Reporter {
 public:
  /**
  * @brief Constructs a candidate to be used in an election.
  *
  *
  * @param[in] int holding a candidate id number
  * @param[in] string containing the candidate's name
  * @param[in] string containing the candidate's party
  *
  */
  explicit Candidate(int, std::string, std::string);
  /**
  * @brief Get candidate id
  * @return candidate id
  */
  int GetID() const;
  /**
  * @brief Get the candidate's name
  * @return string of the candidate's name
  */
  std::string GetName() const;
  /**
  * @brief Get the number of ballots the candidate has
  * @return int of the number of ballots the candidate has
  */
  int GetNumBallots() const;
  /**
  * @brief Add a ballot to the list of ballots the candidate has
  * @param[in] A ballot object
  * @return int of the number of ballots the candidate has
  */
  int AddBallot(Ballot*);

 protected:
  /**
  * @brief Add one to the number of ballots the candidate has
  * @return int of the number of ballots the candidate has
  */
  int IncrementNumBallots();
  std::string name_;  // candidate name
  std::string party_;  // candiate party
  int numBallots_ = 0;  // number of ballots the candidate has
  std::list<Ballot*> ballotList_ = {};  // list of ballots a candidate has
  int id_;  // candidate id number
};
/**
 * @brief The main class for STV candidates.
 *
 * Is an STV candidate.
 */
class STVCandidate : public Candidate {
 public:
    /**
  * @brief Constructs an STV candidate to be used in an STV election.
  *
  *
  * @param[in] int holding an STV candidate id number
  * @param[in] string containing the STV candidate's name
  * @param[in] string containing the STV candidate's party
  *
  */
  explicit STVCandidate(int, std::string, std::string);
  /**
  * @brief Add a ballot to the list of ballots the candidate has
  * @param[in] A ballot object
  * @return int of the number of ballots the candidate has
  */
  int AddBallot(Ballot* ballot);
  /**
  * @brief Remove the list of ballots an STV candidate has
  * @return list of ballots
  */
  std::list<Ballot*> RemoveBallotList();
  /**
  * @brief Save ballot id number for the first ballot given to an STV candiate.
  * @param[in] the ballot id number as an integer.
  */
  void SetFirstBallotNum(int);
  /**
  * @brief Get the ballot id of the first ballot given to the STV candidate
  * @return int of the ballot id number.
  */
  int GetFirstBallotNum() const;

 private:
  /**
  * @brief Sets the number of ballots the STV candidate has to zero
  */
  void SetNumBallotZero();
  int first_Ballot_Num_;  // The ballot id number of the first \
                                ballot given to the STV candidate.
};
#endif  // SRC_CANDIDATE_H_
