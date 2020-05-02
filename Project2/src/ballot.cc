/**
 * @file ballot.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "ballot.h"

Ballot::Ballot(int ballot_id, std::list<int> CandidateList, std::list<int> oriBallot) {
    std::list<int> tempList;
    oriBallot_ = oriBallot;
    tempList = CandidateList;    
    tempList.sort();
    tempList.unique();
    if (ballot_id < 0) {
        throw std::invalid_argument("ballot id can not be negative");
    }
    if (tempList.size() != CandidateList.size()) {
        throw std::
              invalid_argument("candidate list can not contain duplicates");
    }
    id_ = ballot_id;
    rankedCandidateIDList_ = CandidateList;
}

int Ballot::GetID() {
    return id_;
}

std::list<int> Ballot::GetRankedCandidateIDList() {
    return rankedCandidateIDList_;
}

std::list<int> Ballot::GetOriBallot() {
    return oriBallot_;
}
