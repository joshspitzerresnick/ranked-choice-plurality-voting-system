/**
 * @file plurality_election_record.h
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */
#ifndef SRC_PLURALITY_ELECTION_RECORD_H_
#define SRC_PLURALITY_ELECTION_RECORD_H_
#include <list>

#include "candidate.h"
#include "ballot.h"

/**
 * @brief The class for the plurality election records
 *
 * Is a Plurality Election Record - will do most of plurality election work.
 */
class PluralityElectionRecord
{
 public:
  /**
  * @brief Constructs plurality election record with a list of candidates
  *        and list of ballots
  *
  * @param[in] \List of Candidate objects
  * @param[in] List of Ballot objects
  */
  explicit PluralityElectionRecord(std::list<Candidate*>, std::list<Ballot*>);
  /**
  * @brief Deconstructs a Plurality election record container.
  */
  ~PluralityElectionRecord();

  /**
  * @brief Distributes ballots to candidates
  */
  void DistributeBallots();

  /**
  * @brief Sorts the nonElectedCandidateList, candidate with the highest
  *        number of ballots is sent to front of the list
  */
  void SortNonElectedCandidateList();

 /**
  * @brief Moves Candidates from the non elected candidate list to the
  *        winners list
  *
  *@param[in] int Number of candidates to move to the winners list
  */
  void MoveFirstNCandidatesFromNonELectedListToWinnersList(int);

 /**
  * @brief Moves Candidates from the non elected candidate list to the
  *        losers list
  *
  */
  void MoveRemainingCandidatesToLosersList();

  /**
  * @brief Gets the candidates that are not on the winners list or
  * losers list
  * @return list<Candidate*> a list of candidate pointers
  */
  std::list<Candidate*> GetNonElectedCandidateList();

  /**
  * @brief Gets the candidates that are on the winners list
  * @return list<Candidate*> a list of candidate pointers
  */
  std::list<Candidate*> GetWinnersList();

  /**
  * @brief Gets the candidates that are on the losers list
  * @return list<Candidate*> a list of candidate pointers
  */
  std::list<Candidate*> GetLosersList();

  /**
  * @brief Gets the list of ballots that haven't yet been
  * assigned to a candidate
  * @return list<Ballot*> a list of ballot pointers
  */
  std::list<Ballot*> GetNonDistributedBallotList();

 /**
  * @brief Moves Candidates from the non elected candidate list to the
  *        losers list
  *
  *@param[in] int Number of candidates to move to the losers list
  */
  static bool CandidateNumBallotsComp(Candidate*,Candidate*);

 private:
  std::list<Ballot*> nonDistributedBallotList_;
  std::list<Candidate*> nonElectedCandidateList_;
  std::list<Candidate*> winnersList_;
  std::list<Candidate*> losersList_;


};

#endif // SRC_PLURALITY_ELECTION_RECORD_H_
