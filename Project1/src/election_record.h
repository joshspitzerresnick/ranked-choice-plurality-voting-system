/**
 * @file election_record.h
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#ifndef SRC_ELECTION_RECORD_H_
#define SRC_ELECTION_RECORD_H_

#include <list>
#include "candidate.h"
#include "ballot.h"

/**
 * @brief The abstract class for election records.
 *
 * Is an abstract election record.
 */
class ElectionRecord {
 public:
  /**
  * @brief Constructs an abstract election record with a candidate list and ballot list.
  *
  *
  * @param[in] linked list of Candidates
  * @param[in] linked list of ballots
  *
  */
    explicit ElectionRecord(const std::list<Candidate*>,
                            const std::list<Ballot*>);
  /**
  * @brief Election record destructor
  */
    ~ElectionRecord();
    std::list<Ballot*> GetNonDistributedBallotList();
    std::list<Candidate*> GetNonElectedCandidateList();
    std::list<Candidate*> GetWinnersList();
    std::list<Candidate*> GetLosersList();
  /**
  * @brief Virtual function for distributing ballots.
  */
    virtual void DistributeBallots() = 0;
  /**
   * @brief Virtual function for sorting the non elected candidate list.
   */
    virtual void SortNonElectedCandidateList() = 0;
  /**
   * @brief Virtual function for breaking ties between candidates.
   */
    virtual Candidate* BreakTies(Candidate*, Candidate*);

 protected:
  std::list<Ballot*> nonDistributedBallotList_;  // Non Distributed ballot list
  std::list<Candidate*> nonElectedCandidateList_;  // Non elected candidate list
  std::list<Candidate*> winnersList_;  // Winner List
  std::list<Candidate*> losersList_;  // Loser List
};

/**
 * @brief The class for the STV election records
 *
 * Is an STV Election Record - will do most of STV election work.
 */
class STVElectionRecord : public ElectionRecord {
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
    explicit STVElectionRecord(const std::list<STVCandidate*>,
                               const std::list<Ballot*>, int);
  /**
  * @brief STV election record destructor
  */
    ~STVElectionRecord();
  /**
   * @brief Function to shuffle the ballots prior to the election.
   */
    void ShuffleBallots();
  /**
   * @brief Function to distribute the ballots to the canidate of the ballots choosing.
   */
    void DistributeBallots();
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
   * @brief Break a tie between two stv candidates
   * 
   * @param[in] STV candidate 1
   * @param[in] STV candidate 2
   * 
   * @return The winning STV candidate
   */
    STVCandidate* BreakTies(STVCandidate*, STVCandidate*);
  /**
   * @brief Take an stv candidate off the losers list
   * 
   * @return An stv candidate
   */
    STVCandidate* PopCandidateOffLosersList();

 private:
    std::list<Ballot*> discardedBallotList_;  // The discarded ballot list
    int DroopQuota_ = 0;  // The droop quota
};

#endif  // SRC_ELECTION_RECORD_H_
