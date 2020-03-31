/**
 * @file candidate.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "plurality_election_record.h"
#include "election_record.h"

PluralityElectionRecord::PluralityElectionRecord(std::list<Candidate*> candidates, std::list<Ballot*> ballots)
{
    this->nonDistributedBallotList_ = ballots;
    this->nonElectedCandidateList_ = candidates;
}


void PluralityElectionRecord::DistributeBallots()
{

}


Candidate* PluralityElectionRecord::BreakTies(Candidate* candidate_1, Candidate* candidate_2)
{
    return candidate_1;
}

void PluralityElectionRecord::MoveFirstNCandidatesFromNonELectedListToWinnersList(int N)
{

}


void PluralityElectionRecord::MoveFirstNCandidatesFromNonELectedListToLosersList(int N)
{

}

std::list<Ballot*> PluralityElectionRecord::GetNonDistributedBallotList()
{
    return this->nonDistributedBallotList_;
}

std::list<Candidate*> PluralityElectionRecord::GetNonElectedCandidateList()
{
    return this->nonElectedCandidateList_;
}
std::list<Candidate*> PluralityElectionRecord::GetWinnersList()
{
    return this->winnersList_;
}
std::list<Candidate*> PluralityElectionRecord::GetLosersList()
{
    return this->losersList_;
}

void PluralityElectionRecord::SortNonElectedCandidateList()
{

}
