/**
 * @file STVElectionRecord.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "stv_election_record.h"
#include <list>
#include <vector>
#include "candidate.h"
#include "ballot.h"
#include <cstdlib>
#include <algorithm> //std::shuffle
#include <random>  // std::default_random_engine
#include <chrono>  // std::chrono::system_clock
#include <assert.h>

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

void STVElectionRecord::ShuffleBallots() {
  // Call utility function to shuffle ballots
  ListShuffle(nonDistributedBallotList_);
  // Get the sequence after shuffling for logging purpose
  // int ballotSequenceAfterShuffle[nonDistributedBallotList_.size()];
  // int i = 0;
  // std::list<Ballot*>::iterator it;  // Create an iterator of std::list
  // // Make iterate point to begining and incerement it one by one till it reaches the end of list.
  // for (it = nonDistributedBallotList_.begin(); it != nonDistributedBallotList_.end(); it++) {
  //   // Access the object through iterator
  //   ballotSequenceAfterShuffle[i] = (*it)->GetID();
  // }
  // Log ballot sequence after shuffle to logger
  // ----------------Need code-----------------------------
}

void STVElectionRecord::DistributeBallots(int* firstBallotNum) {
  std::list<int> tempRankedCandidateList;  // temperory int array to store ranked candidate list from each ballot
  int curCandidateID;  // current ranked candidate ID
  int numBallots;  // number of ballots a candidate has
  bool assigned;  // if a ballot had been assigned
  Ballot* curBallot;  // a holder for the ballot popped off list
  STVCandidate* tempCandidate;  // pointer to a candidate
  // Loop on nonDistributedBallotList: keep looping if nonDistributedBallotList is not empty
  while (!nonDistributedBallotList_.empty()) {
    curBallot = nonDistributedBallotList_.front();
    nonDistributedBallotList_.pop_front();
    //--------- Log to logger
    //
    assigned = false;  //  initialize
    // Get ranked candidate list
    tempRankedCandidateList = /*(int)*/ curBallot->GetRankedCandidateIDList();
    auto li = tempRankedCandidateList.begin();
    while (!assigned && li != tempRankedCandidateList.end()) {
      std::advance(li, 1);
      // Find the next ranked candidate on nonElectedCandidateList
      curCandidateID = *li;
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
          // check if current candidate met droop
          if (CheckDroop(numBallots)) {
            tempCandidate = *itCandidate;
            nonElectedCandidateList_.erase(itCandidate++);
            AddCandidateToWinnersList(tempCandidate);
            //--------- Log to logger
            //
          }
          assigned = true;
          break;
        }
      }
    }
    if (li == tempRankedCandidateList.end() && !assigned) {
      // did not find a candidate on non elected list for this ballot
      AddBallotToDiscardedBallotList(curBallot);
      //--------- Log to logger
      //
    }
  }
  // delete tempRankedCandidateList;
}

bool STVElectionRecord::CheckDroop(int droop) {
  return ((droop >= DroopQuota_)? true:false);
}

void STVElectionRecord::AddCandidateToWinnersList(STVCandidate* candidate) {
  winnersList_.push_back(candidate);
}

void STVElectionRecord::SortNonElectedCandidateList() {
  nonElectedCandidateList_.sort(STVCandidateComparator);
  // nonElectedCandidateList_.sort([](const STVCandidate &candidate1, const STVCandidate &candidate2)
  //   {
  //     if (candidate1.GetNumBallots() == candidate2.GetNumBallots())
  //       {return candidate1.GetFirstBallotNum()>candidate2.GetFirstBallotNum(); }
  //     return candidate1.GetNumBallots() > candidate2.GetNumBallots();
  //   }
  // );
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
  //--------- Log to logger
  //
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
  if (candidate1->GetNumBallots() == candidate2->GetNumBallots()) {
    return candidate1->GetFirstBallotNum() > candidate2->GetFirstBallotNum();
  } else {
  return candidate1->GetNumBallots() > candidate2->GetNumBallots();
  }
}
