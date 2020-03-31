#include "STVCandidate.h"

STVCandidate::STVCandidate(int id, string name, string party) : Candidate (id, name, party) { };

STVCandidate::STVCandidate(const STVCandidate & rhs) {
    id_ = rhs.id_;
    name_ = rhs.name_;
    party_ = rhs.party_;
    numBallots_ = rhs.numBallots_;  // number of ballots the candidate has
    ballotList_ = rhs.ballotList_;  // list of ballots a candidate has
    first_Ballot_Num_ = rhs.first_Ballot_Num_;
}

STVCandidate & STVCandidate::operator = (const STVCandidate & rhs) {
    if(this != &rhs) {
        id_ = rhs.id_;
        name_ = rhs.name_;
        party_ = rhs.party_;
        numBallots_ = rhs.numBallots_;  // number of ballots the candidate has
        ballotList_ = rhs.ballotList_;  // list of ballots a candidate has
        first_Ballot_Num_ = rhs.first_Ballot_Num_;
    }
    return *this;
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
