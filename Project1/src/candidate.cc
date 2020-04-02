/**
 * @file candidate.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "candidate.h"
#include "ballot.h"

Candidate::Candidate(int candidate_num = 0,
                     std::string candidate_name = "",
                     std::string candidate_party = "") {
    if (candidate_num < 0) {
        throw std::invalid_argument("candidate id cannot be negative");
    }
    id_ = candidate_num;
    name_ = candidate_name;
    party_ = candidate_party;
}

int Candidate::GetID() const {
    return id_;
}

std::string Candidate::GetName() const {
    return name_;
}

int Candidate::GetNumBallots() const {
    return numBallots_;
}

int Candidate::AddBallot(Ballot* ballot) {
    ballotList_.push_back(ballot);
    IncrementNumBallots();
    return numBallots_;
}

int Candidate::IncrementNumBallots() {
    numBallots_++;
    return numBallots_;
}

STVCandidate::STVCandidate(int candidate_num,
                           std::string candidate_name,
                           std::string candidate_party) {
    if (candidate_num < 0) {
        throw std::invalid_argument("candidate id cannot be negative");
    }
    id_ = candidate_num;
    name_ = candidate_name;
    party_ = candidate_party;
    first_Ballot_Num_ = 0;
}

int STVCandidate::AddBallot(Ballot* ballot) {
    if (first_Ballot_Num_ == 0) {
        SetFirstBallotNum(ballot->GetID());
    }
    ballotList_.push_back(ballot);
    IncrementNumBallots();
    return numBallots_;
}

std::list<Ballot*> STVCandidate::RemoveBallotList() {
    std::list<Ballot*> temp_ballot_list = ballotList_;
    ballotList_ = std::list<Ballot*>{};
    SetNumBallotZero();
    return temp_ballot_list;
}

void STVCandidate::SetFirstBallotNum(int ballot_num) {
    if (ballot_num < 0) {
        throw std::invalid_argument("ballot id cannot be negative");
    }
    first_Ballot_Num_ = ballot_num;
}

int STVCandidate::GetFirstBallotNum() const {
    return first_Ballot_Num_;
}

void STVCandidate::SetNumBallotZero() {
    numBallots_ = 0;
}
