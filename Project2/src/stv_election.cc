/**
 * @file stv_election.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "stv_election.h"


STVElection::STVElection(VotingInfo* votingInfo) {
  numSeats_ = votingInfo->GetNumSeats() <= votingInfo->GetNumCandidates() ? votingInfo->GetNumSeats() : votingInfo->GetNumCandidates();
  int numBallots = votingInfo->GetNumBallots();
  int droop = static_cast<int>(floor((static_cast<double>(numBallots))/(static_cast<double>(numSeats_)+1))+1);
  stvElectionRecord_ = new STVElectionRecord(votingInfo->GetSTVCandidateList(),
    votingInfo->GetBallotList(), droop);
}

void STVElection::RunElection(VotingInfo* votingInfo) {

  STVCandidate* candidate;  // stv candidate object pointer to hold candidate object to pass between member functions
  std::list<Ballot*> ballotList;  // ballot pointer list to hold ballots for passing between stvelectionrecord functions
  std::list<STVCandidate*> tempSTVCandidateList;
  int firstBallotNum = 1;
  char msg[2000], temp[100];
  // check if ballot shuffle off option is true
  if (!BallotShuffleOff) {
    stvElectionRecord_->ShuffleBallots();  // shuffle ballots
  }
  while (true) {
    stvElectionRecord_->DistributeBallots(&firstBallotNum);
    tempSTVCandidateList = stvElectionRecord_->GetNonElectedCandidateList();
    // when there is no more candidate on nonelected list, exit loop
    if (tempSTVCandidateList.empty()) {
      break;
    }
    // Sort non-elected candidate list by number of votes, break tie (embeded) if number of votes are equal
    stvElectionRecord_->SortNonElectedCandidateList();
    tempSTVCandidateList = stvElectionRecord_->GetNonElectedCandidateList();
    snprintf(msg, sizeof(msg), "Sorted nonElectedCandidateList: ");
    // Create an iterator of std::list
    std::list<STVCandidate*>::iterator itCandidate;
    for (itCandidate = tempSTVCandidateList.begin(); itCandidate != tempSTVCandidateList.end(); itCandidate++) {
      // Access the object through iterator
      snprintf(temp, sizeof(temp), "%d-%s (%d votes), ",
          (*itCandidate)->GetID(), (*itCandidate)->GetName().c_str(),
          (*itCandidate)->GetNumBallots());
      strncat(msg, temp, sizeof(msg));
    }
    LOGGER->Log(msg);  // Log
    // Put the candidate with the least votes onto losers list and put his/her ballots into non-distributed balots list
    candidate = stvElectionRecord_->RemoveLastCandidateFromNonElectedCandidateList();
    // Logging...
    snprintf(msg, sizeof(msg), "Move candidate %s to losersList", candidate->GetName().c_str());
    LOGGER->Log(msg);
    ballotList = stvElectionRecord_->AddCandidateToLosersList(candidate);    
    tempSTVCandidateList = stvElectionRecord_->GetNonElectedCandidateList();
    // when there is no more candidate on nonelected list, exit loop
    if (tempSTVCandidateList.empty()) {
      LOGGER->Log("No more candidate on nonElectedList");
      break;
    }
    snprintf(msg, sizeof(msg), "Move candidate %s's ballot to nonDistributedBallotList: ", candidate->GetName().c_str());
    LOGGER->Log(msg);
    LOGGER->Log(ballotList);
    stvElectionRecord_->AddLoserBallotsToNonDistributedBallotList(ballotList);
  }
  // if need more candidates to fill seats, move the candidates being put on losers list last to winners list
  while ((int)(stvElectionRecord_->GetWinnersList().size()) < numSeats_) {
    candidate = stvElectionRecord_->PopCandidateOffLosersList();
    snprintf(msg, sizeof(msg), "Move candidate %s from losersList to winnersList.",
                                                  candidate->GetName().c_str());
    LOGGER->Log(msg);
    stvElectionRecord_->AddCandidateToWinnersList(candidate);
  }
  Logger::GetLogger()->Log("----------------------------------------Election Complete-------------------------------------------");
  // display election results
  DisplayResult(votingInfo);
  snprintf(msg, sizeof(msg), "---------------------------------------------------------Election Complete---------------------------------------------------------");
  Logger::GetLogger()->Log(msg);
}

void STVElection::DisplayResult(VotingInfo* votingInfo) {
  std::list<STVCandidate*> winnersList;
  std::list<STVCandidate*> losersList;
  std::list<STVCandidate*>::iterator it;
  int numCandidates;
  int orderNum = 0;
  char msg[1000];
  winnersList = stvElectionRecord_->GetWinnersList();
  losersList = stvElectionRecord_->GetLosersList();
  numCandidates = (int)winnersList.size() + (int)losersList.size();
  snprintf(msg, sizeof(msg), "---------------Election Result----------------");
  LOGGER->Log(msg);
  std::cout << msg << "\n" << std::flush;
  snprintf(msg, sizeof(msg), "* Election Type: STV");
  LOGGER->Log(msg);
  std::cout << msg << std::endl;
  snprintf(msg, sizeof(msg), "* # Ballots: %d", votingInfo->GetNumBallots());
  LOGGER->Log(msg);
  std::cout << msg << std::endl;
  snprintf(msg, sizeof(msg), "* # Invalid ballots: %d", votingInfo->GetNumInvalid());
  LOGGER->Log(msg);
  std::cout << msg << std::endl;
  snprintf(msg, sizeof(msg), "* #Seats: %d", numSeats_);
  LOGGER->Log(msg);
  std::cout << msg << std::endl;
  snprintf(msg, sizeof(msg), "* #Candidates: %d", numCandidates);
  LOGGER->Log(msg);
  std::cout << msg << std::endl;
  snprintf(msg, sizeof(msg), "* Winners are: ");
  LOGGER->Log(msg);
  std::cout << msg << std::endl;
  for (it = winnersList.begin(); it != winnersList.end(); it++) {
    snprintf(msg, sizeof(msg), "  %d: %s", ++orderNum, (*it)->GetName().c_str());
    LOGGER->Log(msg);
    std::cout << msg << "\n" << std::flush;
  }
  orderNum = 0;
  snprintf(msg, sizeof(msg), "* Losers are: ");
  LOGGER->Log(msg);
  std::cout << msg << std::endl;
  for (it = losersList.begin(); it != losersList.end(); it++) {
    snprintf(msg, sizeof(msg), "  %d: %s", ++orderNum, (*it)->GetName().c_str());
    LOGGER->Log(msg);
    std::cout << msg << std::endl;
  }
  snprintf(msg, sizeof(msg), "Location of audit report: \\src\\%s", LogFileName);
  LOGGER->Log(msg);
  std::cout << msg << std::endl;
  snprintf(msg, sizeof(msg), "Location of invalidated ballots report: \\src\\%s", InvalidBallotFileName);
  LOGGER->Log(msg);
  std::cout << msg << std::endl;
  snprintf(msg, sizeof(msg), "-------------End of Result Display------------");
  LOGGER->Log(msg);
  std::cout << msg << std::endl;
}
