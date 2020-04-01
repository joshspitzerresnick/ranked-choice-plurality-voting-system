

#include "stv_election.h"
#include <cmath>

explicit STVElection::STVElection(VotingInfo* votingInfo) {
  numSeats_ = votingInfo->GetNumSeats();
  int numBallots = votingInfo->GetNumBallots();
  int droop = (int)(floor(((double)numBallots)/((double)numSeats_+1))+1);
  stvElectionRecord_ = new stvElectionRecord_(votingInfo.GetCandidateList(), votingInfo.GetBallotList(), droop);
  stvResultDisplay_= new ResultDisplay();
}

STVElection::RunElection(){
  STVCandidate* candidate; // stv candidate object pointer to hold candidate object to pass between member functions
  std::list<Ballot*> ballotList; // ballot pointer list to hold ballots for passing between stvelectionrecord functions
  // check if ballot shuffle off option is true
  if (~BallotShuffleOff){
    stvElectionRecord_->ShuffleBallots(); // shuffle ballots
  }
  while (true){
    stvElectionRecord_->DistributeBallots(); // distribute ballots
    // when there is no more candidate on nonelected list, exit loop
    if (stvElectionRecord_->nonElectedCandidateList_.empty()){
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
  while ((int)(stvElectionRecord_->winnersList_.size()) < numSeats_){
    candidate = stvElectionRecord_->PopCandidateOffLosersList();
    stvElectionRecord_->AddCandidateToWinnersList(candidate);
  }
  // display election results
  stvResultDisplay_->DisplayResult(stvElectionRecord_);
}