/**
 * @file stv_election_record.h
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#ifndef SRC_STV_ELECTION_RECORD_H_
#define SRC_STV_ELECTION_RECORD_H_

#include <list>
#include <map>
#include "candidate.h"
#include "ballot.h"
#include "logger.h"

extern Logger* logger;

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
  explicit STVElectionRecord(std::list<STVCandidate*>, std::list<Ballot*>, int);

  /**
   * @brief Function to get nonDistributedBallotList_.
   *
   * @return list<Ballot*>,
   */
  std::list<Ballot*> GetNonDistributedBallotList();

  /**
   * @brief Method to find a candidate from NonElectedCandidateMap.
   *
   * @param[in] int, ID of candidate
   * @return STVCandidate* with id of input parameter, or NULL if candidate not in map
   */
  STVCandidate* FindCandidate(int);

  /**
   * @brief Method to assign a ballot to a candidate.
   *
   * @param[in] Ballot*, ballot to give to candidate
   * @param[in] STVCandidate*, STVCandidate to assign ballot to
   * @param[in] int, ID of candidate
   */
  void GiveBallotToCandidate(Ballot*, STVCandidate*, int);

  /**
   * @brief Method to check if there are still candidates in NonElectedCandidateMap
   *
   * @return Returns bool, True if there are still candidates in NonElectedCandidateMap
   * else it returns false
   */
  bool ValidCandidatesRemain();

  /**
   * @brief Method to get nonElectedCandidateMap
   *
   * @return map<int, STVCandidate*>, the nonElectedCandidateMap
   */
  std::map<int,STVCandidate*> GetNonElectedCandidateMap();

  /**
   * @brief Method to get winnersList_.
   *
   * @return Returns list<STVCandidate*>
   */
  std::list<STVCandidate*> GetWinnersList();

  /**
   * @brief Method to get losersList_.
   *
   * @return Returns list<STVCandidate*>
   */
  std::list<STVCandidate*> GetLosersList();

  /**
   * @brief Method to shuffle the ballots prior to the election.
   */
  void ShuffleBallots();

  /**
   * @brief Method to perform one round of distributing ballots.
   */
  void DistributeBallots();

  /**
   * @brief Method to check a ballot count against the droop value.
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
   * @brief Add an stv candidate to the losers list
   *
   */
   void AddCandidateToLosersList();

   /**
    * @brief Find the losing candidate
    *
    *@return STVCandidate*, losing candidate
    */
   STVCandidate* GetBiggestLoser();

   /**
    * @brief Break losing candidate tie if there are multiple losing candidates
    *
    *@param[in] list<STVCandidate*> list of the losing stv candidates
    *@return STVCandidate*, losing candidate
    */
   STVCandidate* BreakLoserTie(std::list<STVCandidate*>);

   /**
    * @brief Moves ballots from losers list to winners list
    *
    * @param[in] int, number of places on winners list
    */
  void FillWinnersList(int);

 private:
  template <typename T > void listShuffle( std::list<T> &L ); // utility function for shuffling ballots
  bool CandidateNumBallotsComp(const STVCandidate* candidate1, const STVCandidate* candidate2); // utility function for comparing candidates' votes
  std::list<Ballot*> nonDistributedBallotList_;  // Non Distributed ballot list
  std::map<int,STVCandidate*> nonElectedCandidateMap;
  std::list<STVCandidate*> winnersList_;  // Winner List
  std::list<STVCandidate*> losersList_;  // Loser List
  std::list<Ballot*> discardedBallotList_;  // The discarded ballot list
  int DroopQuota_;  // The droop quota
  int current_ballot_num;
};
#endif
