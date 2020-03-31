/**
 * @file STVElectionRecord.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <list>
#include "candidate.h"
#include "ballot.h"
#include <algorithm> //std::shuffle
#include <vector>
#include <cstdlib>
#include <random>  // std::default_random_engine
#include <chrono>  // std::chrono::system_clock



STVElectionRecord::STVElectionRecord(std::list<STVCandidate*> stvcandidate_list,
                                     std::list<Ballot*> ballot_list,
                                     int droop) {
    // Add code here
}

STVElectionRecord::~STVElectionRecord() {
    // Add code here
}

std::list<Ballot*> ElectionRecord::GetNonDistributedBallotList()
{
    return nonDistributedBallotList_;
};

std::list<STVCandidate*> ElectionRecord::GetNonElectedCandidateList()
{
    return nonElectedCandidateList_;
};

std::list<STVCandidate*> ElectionRecord::GetWinnersList()
{
    return winnersList_;
};

std::list<STVCandidate*> ElectionRecord::GetLosersList()
{
    return losersList_;
};

void STVElectionRecord::ShuffleBallots() {
    // Call utility function to shuffle ballots
    listShuffle( nonDistributedBallotList_ );
    // Log the random number sequence to the logger
    // 
}

// utility function for shuffling ballots
template <class T > void listShuffle( list<T> &L )
{
   unsigned seed = = std::chrono::system_clock::now().time_since_epoch().count();
   vector<T> V( L.begin(), L.end() );
   shuffle( V.begin(), V.end(), default_random_engine(seed) );
   L.assign( V.begin(), V.end() );
}

void STVElectionRecord::DistributeBallots() {
    // Add code here
}

bool STVElectionRecord::CheckDroop(int droop) {
    // Add code here
    return true;
}

void STVElectionRecord::AddCandidateToWinnersList(STVCandidate* candidate) {
    // Add code here
}

void STVElectionRecord::SortNonElectedCandidateList() {
    // Add code here
}

STVCandidate*
STVElectionRecord::RemoveLastCandidateFromNonElectedCandidateList() {
    // Add code here
    STVCandidate* candidate;
    return candidate;
}

std::list<Ballot*>
STVElectionRecord::AddCandidateToLosersList(STVCandidate* candidate) {
    // Add code here
    std::list<Ballot*> ballot_list;
    return ballot_list;
}

void
STVElectionRecord::AddLoserBallotsToNonDistributedBallotList(std::list<Ballot*>
                                                             ballot_list) {
    // Add code here
}

void STVElectionRecord::AddBallotToDiscardedBallotList(Ballot* ballot) {
    // Add code here
}

STVCandidate* STVElectionRecord::BreakTies(STVCandidate* candidate1,
                                           STVCandidate* candidate2) {
    // Add code here
    return candidate1;
}

STVCandidate* STVElectionRecord::PopCandidateOffLosersList() {
    // Add code here
    STVCandidate* candidate;
    return candidate;
}