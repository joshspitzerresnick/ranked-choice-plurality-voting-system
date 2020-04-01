

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
    STVCandidate* candidate;
    std::list<Ballot*> ballotList;
    // check if ballot shuffle off option is true
    if (~BallotShuffleOff){
        stvElectionRecord_->ShuffleBallots();
    }
    while (true){        
        stvElectionRecord_->DistributeBallots();
        if (stvElectionRecord_->nonElectedCandidateList_.empty()){
            break;
        }
        candidate = stvElectionRecord_->RemoveLastCandidateFromNonElectedCandidateList();
        ballotList = stvElectionRecord_->AddCandidateToLosersList(candidate);
        stvElectionRecord_->AddLoserBallotsToNonDistributedBallotList(ballotList);
    }
    if ((int)(stvElectionRecord_->winnersList_.size()) < numSeats_){
        candidate = stvElectionRecord_->PopCandidateOffLosersList();
        stvElectionRecord_->AddCandidateToWinnersList(candidate);
    }
    stvResultDisplay_->DisplayResult(stvElectionRecord_);
}