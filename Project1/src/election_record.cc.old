/**
 * @file STVElectionRecord.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <list>
#include "candidate.h"
#include "ballot.h"
#include "election_record.h"

ElectionRecord::ElectionRecord(const std::list<Candidate*> candidate_list = {},
                               const std::list<Ballot*> ballot_list = {}) {
    // Add code here
}

ElectionRecord::~ElectionRecord() {
    // Add code here
}

std::list<Ballot*> ElectionRecord::GetNonDistributedBallotList()
{
    return nonDistributedBallotList_;
};

std::list<Candidate*> ElectionRecord::GetNonElectedCandidateList()
{
    return nonElectedCandidateList_;
};

std::list<Candidate*> ElectionRecord::GetWinnersList()
{
    return winnersList_;
};

std::list<Candidate*> ElectionRecord::GetLosersList()
{
    return losersList_;
};

void ElectionRecord::DistributeBallots() {
    // Add code here
}

void ElectionRecord::SortNonElectedCandidateList() {
    // Add code here
}

Candidate* ElectionRecord::BreakTies(Candidate* candidate1,
                                     Candidate* candidate2) {
    // Add code here
    return candidate1;
}

STVElectionRecord::STVElectionRecord(std::list<STVCandidate*> stvcandidate_list,
                                     std::list<Ballot*> ballot_list,
                                     int droop) {
    // Add code here
}

STVElectionRecord::~STVElectionRecord() {
    // Add code here
}

void STVElectionRecord::ShuffleBallots() {
    // Add code here
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
