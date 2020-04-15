/**
 * @file STVElectionRecord.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "stv_election_record.h"
#include <list>
#include "candidate.h"
#include "ballot.h"
#include <algorithm> //std::shuffle
#include <vector>
#include <cstdlib>
#include <random>  // std::default_random_engine
#include <chrono>  // std::chrono::system_clock

// forward declaration of helpers
template <typename T > void listShuffle( std::list<T> &L );
// bool STVCandidateComparator(const STVCandidate* candidate1, const STVCandidate* candidate2);
//bool STVElectionRecord::BreakTies(const STVCandidate* candidate1, const STVCandidate* candidate2);

STVElectionRecord::STVElectionRecord(const std::list<STVCandidate*> stvcandidate_list, const std::list<Ballot*> ballot_list, int droop)
 : nonElectedCandidateList_(stvcandidate_list), nonDistributedBallotList_(ballot_list), DroopQuota_(droop),
 winnersList_(0), losersList_(0), discardedBallotList_(0) {
}

// STVElectionRecord::~STVElectionRecord() {
//     // Add code here
// }

std::list<Ballot*> STVElectionRecord::GetNonDistributedBallotList()
{
  return nonDistributedBallotList_;
};

std::list<STVCandidate*> STVElectionRecord::GetNonElectedCandidateList()
{
  return nonElectedCandidateList_;
};

std::list<STVCandidate*> STVElectionRecord::GetWinnersList()
{
  return winnersList_;
};

std::list<STVCandidate*> STVElectionRecord::GetLosersList()
{
  return losersList_;
};

void STVElectionRecord::ShuffleBallots() {
  // Call utility function to shuffle ballots
  listShuffle( nonDistributedBallotList_ );
  // Get the sequence after shuffling for logging purpose
  int ballotSequenceAfterShuffle [(int)nonDistributedBallotList_.size()];
  int i=0;
  std::list<Ballot*>::iterator it; //Create an iterator of std::list
  // Make iterate point to begining and incerement it one by one till it reaches the end of list.
  for (it = nonDistributedBallotList_.begin(); it != nonDistributedBallotList_.end(); it++)
  {
    // Access the object through iterator
    ballotSequenceAfterShuffle[i] = (*it)->GetID();
  }
  // Log ballot sequence after shuffle to logger
  //----------------Need code-----------------------------
}

// utility function for shuffling ballots
template <typename T > void STVElectionRecord::listShuffle( std::list<T> &L )
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::vector<T> V( L.begin(), L.end() );
  std::shuffle( V.begin(), V.end(), std::default_random_engine(seed) );
  L.assign( V.begin(), V.end() );
}

void STVElectionRecord::DistributeBallots() {
  std::list<int> tempRankedCandidateList; // temperory int array to store ranked candidate list from each ballot
  int curCandidateID; // current ranked candidate ID
  int numBallots; // number of ballots a candidate has
  bool assigned; // if a ballot had been assigned
  Ballot* curBallot; // a holder for the ballot popped off list
  STVCandidate* tempCandidate; //pointer to a candidate
  // Loop on nonDistributedBallotList
  while(!nonDistributedBallotList_.empty()) // keep looping if nonDistributedBallotList is not empty
  {
    curBallot = nonDistributedBallotList_.front();
    nonDistributedBallotList_.pop_front();
    //--------- Log to logger
    //
    assigned = false; //initialize
    // Get ranked candidate list
    tempRankedCandidateList = /*(int)*/ curBallot->GetRankedCandidateIDList(); // TODO
    auto li = tempRankedCandidateList.begin();
    while (!assigned && li != tempRankedCandidateList.end()){
      std::advance(li, 1);
      // Find the next ranked candidate on nonElectedCandidateList
      curCandidateID = *li;
      // Create a list Iterator
      std::list<STVCandidate*>::iterator itCandidate;
      for (itCandidate = nonElectedCandidateList_.begin(); itCandidate != nonElectedCandidateList_.end(); itCandidate++){
        if ((*itCandidate)->GetID() == *li){
          numBallots = (*itCandidate)->AddBallot(curBallot);
          //check if current candidate met droop
          if (CheckDroop(numBallots))
          {
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
    if (li == tempRankedCandidateList.end() && !assigned){
    AddBallotToDiscardedBallotList(curBallot);  // did not find a candidate on non elected list for this ballot
    //--------- Log to logger
    //
    }
  }
  // delete tempRankedCandidateList; // NOT ALLOCATED - Josh
}

bool STVElectionRecord::CheckDroop(int droop) {
  return ((droop >= DroopQuota_)? true:false);
}

void STVElectionRecord::AddCandidateToWinnersList(STVCandidate* candidate) {
  winnersList_.push_back(candidate);
}

struct STVCandidateComparator
{
	// Compare 2 STVCandidate objects using number of ballots and order received
	bool operator ()(const STVCandidate* candidate1, const STVCandidate* candidate2)
	{
		if (candidate1->GetNumBallots() == candidate2->GetNumBallots())
        {return candidate1->GetFirstBallotNum()>candidate2->GetFirstBallotNum(); }
      return candidate1->GetNumBallots() > candidate2->GetNumBallots();
	}
};

void STVElectionRecord::SortNonElectedCandidateList() {
  nonElectedCandidateList_.sort(STVCandidateComparator());
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
  nonDistributedBallotList_.assign(ballot_list.begin(),ballot_list.end());
}

void STVElectionRecord::AddBallotToDiscardedBallotList(Ballot* ballot) {
  discardedBallotList_.push_front(ballot);
}

// bool STVElectionRecord::BreakTies(const STVCandidate* candidate1, const STVCandidate* candidate2) {
//   return candidate1->GetFirstBallotNum()>candidate2->GetFirstBallotNum();
// }

STVCandidate* STVElectionRecord::PopCandidateOffLosersList() {
  STVCandidate* candidate;
  candidate = losersList_.back();
  losersList_.pop_back();
  //--------- Log to logger
  //
  return candidate;
}

// utility function for comparing candidates' votes
// bool STVElectionRecord::STVCandidateComparator(const STVCandidate* candidate1, const STVCandidate* candidate2) {
//   if (candidate1->GetNumBallots() == candidate2->GetNumBallots()){
//     return candidate1->GetFirstBallotNum()>candidate2->GetFirstBallotNum();
//   }
//   else {
//   return candidate1->GetNumBallots() > candidate2->GetNumBallots();
//   }
// }
