/**
 * @file candidate.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "candidate.h"
#include "ballot.h"

Candidate::Candidate(int, std::string, std::string) {
    // Add code here
}

int Candidate::GetID() {
    // Add code here
    return -1;
}
std::string Candidate::GetName() {
    // Add code here
    return "name";
}

int Candidate::GetNumBallots() {
    // Add code here
    return -1;
}

int Candidate::AddBallot(Ballot) {
    // Add code here
    return -1;
}

int IncrementNumBallots() {
    return -1;
}

STVCandidate::STVCandidate(int, std::string, std::string) {
    // Add code here
}

std::list<Ballot> STVCandidate::RemoveBallotList() {
    std::list<Ballot> ballotList;
    return ballotList;
}

void STVCandidate::SetFirstBallotNum(int) {
    // Add code here
}

int STVCandidate::GetFirstBallotNum() {
    // Add code here
    return -1;
}

void STVCandidate::SetNumBallotZero() {
    // Add code here
}
