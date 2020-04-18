/**
 * @file stv_election.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "stv_election.h"
// #include "voting_system.cc"
#include <cmath>
#include <iostream>
#include <assert.h>

STVElection::STVElection(VotingInfo* votingInfo) {
  numSeats_ = votingInfo->GetNumSeats();
  int numBallots = votingInfo->GetNumBallots();
  int droop = static_cast<int>(floor((static_cast<double>(numBallots))/(static_cast<double>(numSeats_)+1))+1);
  stvElectionRecord_ = new STVElectionRecord(votingInfo->GetSTVCandidateList(),
    votingInfo->GetBallotList(), droop);
}

void STVElection::RunElection() {
  STVCandidate* candidate;  // stv candidate object pointer to hold candidate object to pass between member functions
  std::list<Ballot*> ballotList;  // ballot pointer list to hold ballots for passing between stvelectionrecord functions
  std::list<STVCandidate*> tempSTVCandidateList;
  // check if ballot shuffle off option is true
  if (!BallotShuffleOff) {
    stvElectionRecord_->ShuffleBallots();  // shuffle ballots    
  }
  while (true) {
    stvElectionRecord_->DistributeBallots();  // distribute ballots
    // when there is no more candidate on nonelected list, exit loop
    tempSTVCandidateList = stvElectionRecord_->GetNonElectedCandidateList();
    if (tempSTVCandidateList .empty()) {
      break;
    }
    
    // Sort non-elected candidate list by number of votes, break tie (embeded) if number of votes are equal
    stvElectionRecord_->SortNonElectedCandidateList();
    // Put the candidate with the least votes onto losers list and put his/her ballots into non-distributed balots list
    candidate = stvElectionRecord_->RemoveLastCandidateFromNonElectedCandidateList();
    tempSTVCandidateList = stvElectionRecord_->GetNonElectedCandidateList();
    std::cout << "election2: nonElectedCandidateList_.size()=" << tempSTVCandidateList.size() << "\n";
    ballotList = stvElectionRecord_->AddCandidateToLosersList(candidate);
    stvElectionRecord_->AddLoserBallotsToNonDistributedBallotList(ballotList);
  }
  // if need more candidates to fill seats, move the candidates being put on losers list last to winners list
  while ((int)(stvElectionRecord_->GetWinnersList().size()) < numSeats_){
    candidate = stvElectionRecord_->PopCandidateOffLosersList();
    stvElectionRecord_->AddCandidateToWinnersList(candidate);
  }
  // display election results
  DisplayResult();
}

void STVElection::DisplayResult(){
  std::list<STVCandidate*> winnersList;
  std::list<STVCandidate*> losersList;
  std::list<STVCandidate*>::iterator it;
  int numCandidates;
  int orderNum = 0;
  winnersList = stvElectionRecord_->GetWinnersList();
  losersList = stvElectionRecord_->GetLosersList();
  numCandidates = (int)winnersList.size() + (int)losersList.size();
  std::cout << "---------------Election Result-----------------\n" << std::flush;
  std::cout << "* Election Type: STV" << std::endl;
  std::cout << "* #Seats: " << numSeats_ << std::endl;
  std::cout << "* #Candidates: " << numCandidates << std::endl;
  std::cout << "* Winners are: " << std::endl;
  for (it = winnersList.begin(); it != winnersList.end(); it++) {
    std::cout << ++orderNum << ": " << (*it)->GetName() << "\n" << std::flush;
  }
  orderNum = 0;
  std::cout << "* Losers are: " << std::endl;
  for (it = losersList.begin(); it != losersList.end(); it++) {
    std::cout << ++orderNum << ": " << (*it)->GetName() << std::endl;
  }
  std::cout << "-------------End of Result Display-------------" << std::endl;
}
