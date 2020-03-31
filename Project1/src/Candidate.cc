/**
 * @file candidate.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "Candidate.h"
#include "Ballot.h"
using namespace std;

// Candidate::Candidate(int candidate_num = -1,
//                      std::string candidate_name = "Fred",
//                      std::string candidate_party = "Ind") {
//     id_ = candidate_num;
//     name_ = candidate_name;
//     party_ = candidate_party;
// }
Candidate::Candidate(int id, string name, string party) : id_(id), name_(name), party_(party) {};

Candidate::Candidate(const Candidate & rhs) {
    id_ = rhs.id_;
    name_ = rhs.name_;
    party_ = rhs.party_;
    numBallots_ = rhs.numBallots_;  // number of ballots the candidate has
    ballotList_ = rhs.ballotList_;  // list of ballots a candidate has
}

Candidate & Candidate::operator = (const Candidate & rhs) {
    if(this != &rhs) {
        id_ = rhs.id_;
        name_ = rhs.name_;
        party_ = rhs.party_;;
        numBallots_ = rhs.numBallots_;  // number of ballots the candidate has
        ballotList_ = rhs.ballotList_;  // list of ballots a candidate has
    }
    return *this;
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