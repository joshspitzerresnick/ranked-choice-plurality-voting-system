/**
 * @file stv_election_record.h
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#ifndef SRC_STV_ELECTION_RECORD_H_
#define SRC_STV_ELECTION_RECORD_H_

#include <list>
#include "candidate.h"
#include "ballot.h"
#include "logger.h"
#include <vector>
#include "candidate.h"
#include "ballot.h"
#include <cstdlib>
#include <string.h>
#include <algorithm> //std::shuffle
#include <random>  // std::default_random_engine
#include <chrono>  // std::chrono::system_clock

/**
 * @brief The class for the STV election records
 *
 * Is an STV Election Record - will do most of STV election work.
 */
class STVElectionRecord {
 public:
   /**
  * @brief Constructs an stv election record with a candidate list, ballot list, and droop value.
  *
  *
  * @param[in] linked list of Candidates
  * @param[in] linked list of ballots
  * @param[in] droop value
  *
  */
  STVElectionRecord(const std::list<STVCandidate*>,
                               const std::list<Ballot*>, int);
  /**
   * @brief Function to get nonDistributedBallotList_.
   */
  std::list<Ballot*> GetNonDistributedBallotList();
  /**
   * @brief Function to get nonElectedCandidateList_.
   */
  std::list<STVCandidate*> GetNonElectedCandidateList();
  /**
   * @brief Function to get winnersList_.
   */
  std::list<STVCandidate*> GetWinnersList();
  /**
   * @brief Function to get losersList_.
   */
  std::list<STVCandidate*> GetLosersList();
  /**
   * @brief Returns droop quota.
   *
   * @return int holding droop quota.
   */
  int GetDroop();
  /**
   * @brief Function to shuffle the ballots prior to the election.
   */
  void ShuffleBallots();
  /**
   * @brief Function to distribute the ballots to the canidate of the ballots choosing.
   */
  void DistributeBallots(int*);
  /**
   * @brief Function to check a ballot count against the droop value.
   *
   * @param[in] A ballot count.
   *
   * @return Returns a bool of true if droop has been met and false otherwise.
   */
  bool CheckDroop(int);
  /**
   * @brief Add an stv candidate to the winners list.
   *
   * @param[in] An stv candidate
   */
  void AddCandidateToWinnersList(STVCandidate*);
  /**
   * @brief Sort the non elected candidate list
   */
  void SortNonElectedCandidateList();
  /**
   * @brief Remove the last candidate from the non elected candidate list
   *
   * @return The last stv candidate from the non elected candidates list
   */
  STVCandidate* RemoveLastCandidateFromNonElectedCandidateList();
  /**
   * @brief Add an stv candidate to the losers list
   *
   * @param[in] an stv candidate
   *
   * @return A list of the losers ballots.
   */
  std::list<Ballot*> AddCandidateToLosersList(STVCandidate*);
  /**
   * @brief Add the ballots from a losing candidate back into the non distributed ballots list
   *
   * @param[in] A list of ballots
   */
  void AddLoserBallotsToNonDistributedBallotList(std::list<Ballot*>);
  /**
   * @brief Add ballot to discared ballot list
   *
   * @param[in] A ballot
   */
  void AddBallotToDiscardedBallotList(Ballot*);
  /**
   * @brief Take an stv candidate off the losers list
   *
   * @return An stv candidate
   */
  STVCandidate* PopCandidateOffLosersList();

 private:
  /**
   * @brief Private utility function for shuffling ballots
   *
   * @return Shuffled list
   */
  template <typename T > void ListShuffle(std::list<T> &L);
  /**
   * @brief Private utility function for comparing candidates' votes
   *
   * @return bool: whether candidate1 has more votes than candidate2
   */
  static bool STVCandidateComparator(STVCandidate* candidate1,
                               STVCandidate* candidate2);
  std::list<Ballot*> nonDistributedBallotList_;  // Non Distributed ballot list
  std::list<STVCandidate*> nonElectedCandidateList_;
                  // Non elected candidate list
  std::list<STVCandidate*> winnersList_;  // Winner List
  std::list<STVCandidate*> losersList_;  // Loser List
  std::list<Ballot*> discardedBallotList_;  // The discarded ballot list
  int DroopQuota_;  // The droop quota
};
#endif  // SRC_STV_ELECTION_RECORD_H_
