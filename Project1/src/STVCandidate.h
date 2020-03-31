/**
 * @file STVCandidate.h
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */


#ifndef STVCANDIDATE_H_
#define STVCANDIDATE_H_

#include <iostream>
#include <string>
#include <list>
#include "Candidate.h"
#include "Ballot.h"

/**
 * @brief The main class for STV candidates.
 *
 * Is an STV candidate.
 */
class STVCandidate : public Candidate {
 public:
 /**
  * @brief Default constructor for development phase. Constructs an STV candidate with no input
  *
  *
  * @param[in] none
  * @param[in] none
  *
  */
 STVCandidate(){};
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
  * @brief Remove the list of ballots an STV candidate has
  * @return list of ballots
  */
  STVCandidate(const STVCandidate &); // copy constructor
  STVCandidate & operator = (const STVCandidate &); // copy operator
  std::list<Ballot> RemoveBallotList();
  /**
  * @brief Save ballot id number for the first ballot given to an STV candiate.
  * @param[in] the ballot id number as an integer.
  */
  void SetFirstBallotNum(int);
  /**
  * @brief Get the ballot id of the first ballot given to the STV candidate
  * @return int of the ballot id number.
  */
  int GetFirstBallotNum();
  /**
  * @brief Overload operator = for STVCandidate
  * @param[in] An STVCandidate object
  * @return An STVCandidate object
  */
  STVCandidate* operator = (STVCandidate *c) 
    { 
        return this; 
    };  
 private:
  /**
  * @brief Sets the number of ballots the STV candidate has to zero
  */
  void SetNumBallotZero();
  int first_Ballot_Num_;  // The ballot id number of the first \
                                ballot given to the STV candidate.
};
#endif  // SRC_STVCANDIDATE_H_