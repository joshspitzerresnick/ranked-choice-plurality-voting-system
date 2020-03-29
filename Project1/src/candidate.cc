/**
 * @file candidate.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "candidate.h"
#include "ballot.h"

Candidate::Candidate(int candidate_num = -1,
                     std::string candidate_name = "Fred",
                     std::string candidate_party = "Ind") {
    id_ = candidate_num;
    name_ = candidate_name;
    party_ = candidate_party;
}

int Candidate::GetID() {
    return id_;
}

std::string Candidate::GetName() {
    return name_;
}

int Candidate::GetNumBallots() {
    return numBallots_;
}

int Candidate::AddBallot(Ballot) {
    return numBallots_;
}

int Candidate::IncrementNumBallots() {
    numBallots_++;
    return numBallots_;
}

STVCandidate::STVCandidate(int candidate_num,
                           std::string candidate_name,
                           std::string candidate_party) {
    id_ = candidate_num;
    name_ = candidate_name;
    party_ = candidate_party;
}

std::list<Ballot> STVCandidate::RemoveBallotList() {
    return ballotList_;
}

void STVCandidate::SetFirstBallotNum(int ballot_num) {
    first_Ballot_Num_ = ballot_num;
}

int STVCandidate::GetFirstBallotNum() {
    return first_Ballot_Num_;
}

void STVCandidate::SetNumBallotZero() {
    numBallots_ = 0;
}
