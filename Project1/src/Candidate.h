/**
 * @file Candidate.h
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */


#ifndef SRC_CANDIDATE_H_
#define SRC_CANDIDATE_H_

#include <iostream>
#include <string>
#include <list>
#include "Ballot.h"

/**
 * @brief The main class for candidates.
 *
 * Is a candidate.
 */
class Candidate {  // : public Reporter {
 public:
 /**
  * @brief Default constructor for development phase. Constructs a candidate with no input
  *
  *
  * @param[in] none
  * @param[in] none
  *
  */
  Candidate() {};
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
  Candidate(const Candidate &); // copy constructor
  Candidate & operator = (const Candidate &); // copy operator
  /**
  * @brief Get candidate id
  * @return candidate id
  */
  
  int GetID();
  /**
  * @brief Get the candidate's name
  * @return string of the candidate's name
  */
  std::string GetName();
  /**
  * @brief Get the number of ballots the candidate has
  * @return int of the number of ballots the candidate has
  */
  int GetNumBallots();
  /**
  * @brief Add a ballot to the list of ballots the candidate has
  * @param[in] A ballot object
  * @return int of the number of ballots the candidate has
  */
  int AddBallot(Ballot);
  /**
  * @brief Overload operator = for Candidate
  * @param[in] A Candidate object
  * @return A Candidate object
  */
  Candidate* operator = (Candidate *c) 
    { 
        return this; 
    };  
  

 protected:
  /**
  * @brief Add one to the number of ballots the candidate has
  * @return int of the number of ballots the candidate has
  */
  int IncrementNumBallots();
  std::string name_;  // candidate name
  std::string party_;  // candiate party
  int numBallots_;  // number of ballots the candidate has
  std::list<Ballot> ballotList_;  // list of ballots a candidate has
  int id_;  // candidate id number
};
#endif  // SRC_CANDIDATE_H_