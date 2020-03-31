/**
 * @file ballot.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "Ballot.h"

Ballot::Ballot(int ballot_id, std::list<int> CandidateList) {
    std::list<int> tempList;
    tempList = CandidateList;
    tempList.sort();
    tempList.unique();
    try {
        if (ballot_id < 0) {
            throw 1;
        }
        if (tempList.size() != CandidateList.size()) {
            throw 2;
        }
    id_ = ballot_id;
    rankedCandidateIDList_ = CandidateList;
    }
    catch (int e) {
        if (e == 1) {
            std::cout << "Ballot ID can not be negative." << '\n';
        }
        if (e == 2) {
            std::cout << "Candidate list can not contain duplicates." << '\n';
        }
    }
}

Ballot::Ballot(const Ballot & rhs) {
    id_ = rhs.id_;
    rankedCandidateIDList_ = rhs.rankedCandidateIDList_;
}

Ballot & Ballot::operator = (const Ballot & rhs) {
    if(this != &rhs) {
        id_ = rhs.id_;
        rankedCandidateIDList_ = rhs.rankedCandidateIDList_;
    }
    return *this;
}

int Ballot::GetID() {
    return id_;
}

std::list<int> Ballot::GetRankedCandidateIDList() {
    return rankedCandidateIDList_;
}
