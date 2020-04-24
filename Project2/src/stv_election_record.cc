/**
 * @file STVElectionRecord.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "stv_election_record.h"

STVElectionRecord::STVElectionRecord
(std::list<STVCandidate*> candidates, std::list<Ballot*> ballots, int droop) {
    this->nonDistributedBallotList_ = ballots;
    this->nonElectedCandidateList_ = candidates;
    this->winnersList_ = {};
    this->losersList_ = {};
    this->discardedBallotList_ = {};
    this->DroopQuota_ = droop;
}

std::list<Ballot*> STVElectionRecord::GetNonDistributedBallotList() {
  return nonDistributedBallotList_;
}

std::list<STVCandidate*> STVElectionRecord::GetNonElectedCandidateList() {
  return nonElectedCandidateList_;
}

std::list<STVCandidate*> STVElectionRecord::GetWinnersList() {
  return winnersList_;
}

std::list<STVCandidate*> STVElectionRecord::GetLosersList() {
  return losersList_;
}

int STVElectionRecord::GetDroop() {
  return DroopQuota_;
}

void STVElectionRecord::ShuffleBallots() {
  char msg[1000], temp[10];
  // Call utility function to shuffle ballots
  ListShuffle(nonDistributedBallotList_);
  // Log the sequence after shuffling
  snprintf(msg, sizeof(msg), "Ballot sequence after shuffle: ");
  LOGGER->Log(msg);
  LOGGER->Log(nonDistributedBallotList_);
}

void STVElectionRecord::DistributeBallots(int* firstBallotNum) {
  std::list<int> tempRankedCandidateIDList;  // temperory int array to store ranked candidate list from each ballot
  // int curCandidateID;  // current ranked candidate ID
  int numBallots;  // number of ballots a candidate has
  bool assigned;  // if a ballot had been assigned
  Ballot* curBallot;  // a holder for the ballot popped off list
  STVCandidate* tempCandidate;  // pointer to a candidate
  char msg[1000], temp[10];
  // Loop on nonDistributedBallotList: keep looping if nonDistributedBallotList is not empty
  while (!nonDistributedBallotList_.empty()) {
    curBallot = nonDistributedBallotList_.front();
    nonDistributedBallotList_.pop_front();
    assigned = false;  //  initialize
    // Get ranked candidate list
    tempRankedCandidateIDList = /*(int)*/ curBallot->GetRankedCandidateIDList();
    snprintf(msg, sizeof(msg), "Ballot %d RankedCandidateIDList: ", curBallot->GetID());
    LOGGER->Log(msg);
    LOGGER->Log(tempRankedCandidateIDList);
    auto li = tempRankedCandidateIDList.begin();
    while (!assigned && li != tempRankedCandidateIDList.end()) {
      // Create a list Iterator
      std::list<STVCandidate*>::iterator itCandidate;
      for (itCandidate = nonElectedCandidateList_.begin();
      itCandidate != nonElectedCandidateList_.end(); itCandidate++) {
        if ((*itCandidate)->GetID() == *li) {
          if ((*itCandidate)->GetNumBallots() < 1) {
            // Assign first ballot number
            (*itCandidate)->SetFirstBallotNum((*firstBallotNum)++);
          }
          numBallots = (*itCandidate)->AddBallot(curBallot);
          snprintf(msg, sizeof(msg), "Ballot#%d is assigned to candidate %d-%s", curBallot->GetID(), (*itCandidate)->GetID(), (*itCandidate)->GetName().c_str());
          LOGGER->Log(msg);
          // check if current candidate met droop
          if (CheckDroop(numBallots)) {
            tempCandidate = *itCandidate;
            nonElectedCandidateList_.erase(itCandidate++);
            AddCandidateToWinnersList(tempCandidate);
            //--------- Log to logger
            snprintf(msg, sizeof(msg), "candidate %s met droop, move to winnersList", tempCandidate->GetName().c_str());
            LOGGER->Log(msg);
          }
          assigned = true;
          break;
        }
      }
      // Find the next ranked candidate on nonElectedCandidateList
      std::advance(li, 1);
    }
    if (li == tempRankedCandidateIDList.end() && !assigned) {
      // did not find a candidate on non elected list for this ballot
      AddBallotToDiscardedBallotList(curBallot);
      //--------- Log to logger
      snprintf(msg, sizeof(msg), "Ballot#%d is discarded", curBallot->GetID());
      LOGGER->Log(msg);
    }
  }
}

bool STVElectionRecord::CheckDroop(int droop) {
  return ((droop >= DroopQuota_)? true:false);
}

void STVElectionRecord::AddCandidateToWinnersList(STVCandidate* candidate) {
  winnersList_.push_back(candidate);
}

void STVElectionRecord::SortNonElectedCandidateList() {
  nonElectedCandidateList_.sort(STVCandidateComparator);
}

STVCandidate*
STVElectionRecord::RemoveLastCandidateFromNonElectedCandidateList() {
  STVCandidate* candidate;
  candidate = nonElectedCandidateList_.back();
  nonElectedCandidateList_.pop_back();
  return candidate;
}

std::list<Ballot*>
STVElectionRecord::AddCandidateToLosersList(STVCandidate* candidate) {
  losersList_.push_back(candidate);
  std::list<Ballot*> ballot_list = candidate->RemoveBallotList();
  return ballot_list;
}

void
STVElectionRecord::AddLoserBallotsToNonDistributedBallotList(std::list<Ballot*>
                                                             ballot_list) {
  nonDistributedBallotList_.assign(ballot_list.begin(), ballot_list.end());
}

void STVElectionRecord::AddBallotToDiscardedBallotList(Ballot* ballot) {
  discardedBallotList_.push_front(ballot);
}

STVCandidate* STVElectionRecord::PopCandidateOffLosersList() {
  STVCandidate* candidate;
  candidate = losersList_.back();
  losersList_.pop_back();
  return candidate;
}

template <typename T > void STVElectionRecord::ListShuffle(std::list<T> &L) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::vector<T> V(L.begin(), L.end());
  std::shuffle(V.begin(), V.end(), std::default_random_engine(seed));
  L.assign(V.begin(), V.end());
}

// utility function for comparing candidates' votes
bool STVElectionRecord::STVCandidateComparator(STVCandidate* candidate1, STVCandidate* candidate2) {
  char msg[1000];
  if (candidate1->GetNumBallots() == candidate2->GetNumBallots()) {
    snprintf(msg, sizeof(msg), "Tie break between candidate %d-%s (#votes=%d, #1stBallot=%d) and candidate %d-%s (#votes=%d, #1stBallot=%d).",
        candidate1->GetID(), candidate1->GetName().c_str(), candidate1->GetNumBallots(), candidate1->GetFirstBallotNum(),
        candidate2->GetID(), candidate2->GetName().c_str(), candidate2->GetNumBallots(), candidate2->GetFirstBallotNum());
    LOGGER->Log(msg);
    return candidate1->GetFirstBallotNum() < candidate2->GetFirstBallotNum();
  } else {
  return candidate1->GetNumBallots() > candidate2->GetNumBallots();
  }
}
