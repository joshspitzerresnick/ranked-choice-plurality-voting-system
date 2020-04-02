/**
 * @file stv_election.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "stv_election.h"
// #include "voting_system.cc"
#include <cmath>
#include <iostream>

STVElection::STVElection(VotingInfo* votingInfo) {
  numSeats_ = votingInfo->GetNumSeats();
  int numBallots = votingInfo->GetNumBallots();
  int droop = (int)(floor(((double)numBallots)/((double)numSeats_+1))+1);
  stvElectionRecord_ = new STVElectionRecord(votingInfo->GetSTVCandidateList(), votingInfo->GetBallotList(), droop);
  // stvResultDisplay_= new ResultDisplay(); // NO LONGER USING - Josh
}

void STVElection::RunElection(){
  STVCandidate* candidate; // stv candidate object pointer to hold candidate object to pass between member functions
  std::list<Ballot*> ballotList; // ballot pointer list to hold ballots for passing between stvelectionrecord functions
  // check if ballot shuffle off option is true
  if (!BallotShuffleOff){
    stvElectionRecord_->ShuffleBallots(); // shuffle ballots
  }
  while (true){
    stvElectionRecord_->DistributeBallots(); // distribute ballots
    // when there is no more candidate on nonelected list, exit loop
    if (stvElectionRecord_->GetNonElectedCandidateList().empty()){
      break;
    }
    // Sort non-elected candidate list by number of votes, break tie (embeded) if number of votes are equal
    stvElectionRecord_->SortNonElectedCandidateList();
    // Put the candidate with the least votes onto losers list and put his/her ballots into non-distributed balots list
    candidate = stvElectionRecord_->RemoveLastCandidateFromNonElectedCandidateList();
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
  std::cout << "* Election Type: STV\n" << std::flush;
  std::cout << "* #Seats: " << numSeats_ << "\n" << std::flush;
  std::cout << "* #Candidates: " << numCandidates << "\n" << std::flush;
  std::cout << "* Winners are: " << "\n" << std::flush;
  for (it = winnersList.begin(); it != winnersList.end(); it++)
  {
    std::advance(it, 1);
    std::cout << ++orderNum << ": " << (*it)->GetName() << "\n" << std::flush;
  }
  orderNum = 0;
  for (it = losersList.begin(); it != losersList.end(); it++)
  {
    std::advance(it, 1);
    std::cout << ++orderNum << ": " << (*it)->GetName() << "\n" << std::flush;
  }
  std::cout << "-------------End of Result Display-------------\n" << std::flush;
}
