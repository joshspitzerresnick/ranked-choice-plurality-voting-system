/**
 * @file voting_info.h
 *
 * @copyright 2020 5801 Team3, all rights reserved
 */

#ifndef SRC_VOTING_INFO_H_
#define SRC_VOTING_INFO_H_

#include <iostream>
#include <string>
#include <list>

#include "candidate.h"
#include "ballot.h"

/**
 * @brief The main class for storing voting information.
 *
 * Is a voting information container.
 */
class VotingInfo {
 public:
  /**
  * @brief Constructs a voting info container with an algorithm choice and
  *        number of seats available.
  *
  * @param[in] int holding choice of algorithm (0 for plurality, 1 for STV).
  * @param[in] int holding number of seats available.
  */
  explicit VotingInfo(int = -1, int = -1);
  /**
  * @brief Deconstructs a voting info container.
  */
  ~VotingInfo();
  /**
  * @brief Returns choice of algorithm.
  *
  * @return int holding choice of algorithm (0 for plurality, 1 for STV).
  */
  int GetAlgorithm() const;
  /**
  * @brief Returns number of seats available.
  *
  * @return int holding number of seats available.
  */
  int GetNumSeats() const;
  /**
  * @brief Adds a candidate to the list of candidates.
  *        Sends message to perror and silently fails if try to add candidate
  *        with same id_.
  *
  * @param[in] Candidate* holding a candidate to be added.
  */
  void AddCandidateToCandidateList(Candidate*);
  /**
  * @brief Adds an STV candidate to the list of candidates.
  *        Sends message to perror and silently fails if try to add candidate
  *        with same id_.
  *
  * @param[in] STVCandidate* holding an STV candidate to be added.
  */
  void AddCandidateToCandidateList(STVCandidate*);
  /**
  * @brief Adds a ballot to the list of ballots.
  *        Sends message to perror and silently fails if try to add ballot
  *        with same id_.
  *
  * @param[in] Ballot* holding a ballot to be added.
  */
  void AddBallotToBallotList(Ballot*);
  /**
   * @brief Adds a ballot to the list of invalid ballots.
   *        Sends message to perror and silently fails if try to add ballot
   *        with same id_.
   *
   * @param[in] Ballot* holding a ballot to be added.
   */
  void AddBallotToInvalidList(Ballot*);
  /**
  * @brief Returns number of candidates in candidate list.
  *
  * @return int holding number of candidates in candidate list.
  */
  int GetNumCandidates() const;
  /**
  * @brief Returns number of ballots in ballot list.
  *
  * @return int holding number of ballots in ballot list.
  */
  int GetNumBallots() const;
  /**
   * @brief Returns number of ballots in invalid ballot list.
   * 
   * @return int holding number of ballots in invalid ballot list.
   */
  int GetNumInvalid() const;
  /**
  * @brief Returns list of candidates.
  *
  * @return std::list<Candidate*> holding list of candidates.
  */
  std::list<Candidate*> GetCandidateList() const;
  /**
  * @brief Returns list of STV candidates.
  *
  * @return std::list<STVCandidate*> holding list of candidates.
  */
  std::list<STVCandidate*> GetSTVCandidateList() const;
  /**
  * @brief Returns list of ballots.
  *
  * @return std::list<Ballot*> holding list of ballots.
  */
  std::list<Ballot*> GetBallotList() const;
  /**
   * @brief Returns list of invalid ballots.

   *
   * @return std::list<Ballot*> holding list of invalid ballots.
   */
  std::list<Ballot*> GetInvalidList() const;
  /**
  * @brief Writes report of all invalidated ballots (less than half of
  *        candidates ranked) from an STV election to a specified filename.
  *
  * @param[in] std::string holding a filename for report to be written to.
  */
  void WriteInvalidBallotsToFile(std::string filename);
  /**
   * @brief Log to audit file.
   * 
   * @return void.
   */
  void LogToAuditFile();

 private:
  void IncrementNumCandidates();
  void IncrementNumBallots();
  void IncrementNumInvalid();
  int algorithm_;
  int num_seats_;
  int num_candidates_;
  std::list<Candidate*> candidate_list_;
  std::list<STVCandidate*> stv_candidate_list_;
  int num_ballots_;
  std::list<Ballot*> ballot_list_;
  int num_invalid_;
  std::list<Ballot*> invalid_list_;
};
#endif  // SRC_VOTING_INFO_H_