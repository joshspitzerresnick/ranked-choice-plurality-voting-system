
#ifndef ELECTIONRECORD_H_
#define ELECTIONRECORD_H_

#include <list>
#include "Candidate.h"
#include "Ballot.h"
// #include "ballot.h"
// #include "candidate.h"

class ElectionRecord
{
protected:
    std::list<Ballot*> nonDistributedBallotList_;
    std::list<Candidate*> nonElectedCandidateList_;
    std::list<Candidate*> winnersList_;
    std::list<Candidate*> losersList_;

public:
    ElectionRecord();
    // ElectionRecord(std::list<Ballot*> nonDistributedBallotList, std::list<Candidate*> nonElectedCandidateList) : 
    // nonDistributedBallotList_(nonDistributedBallotList), nonElectedCandidateList_(nonElectedCandidateList),
    // winnersList_{0}, losersList_{0} {}; 
    // ElectionRecord(const ElectionRecord &); // copy constructor
    // ElectionRecord & operator = (const ElectionRecord &); // copy operator 
    ~ElectionRecord() {};
    std::list<Ballot*> GetNonDistributedBallotList();
    std::list<Candidate*> GetNonElectedCandidateList();
    std::list<Candidate*> GetWinnersList();
    std::list<Candidate*> GetLosersList();
    virtual void DistributeBallots() = 0;
    virtual void SortNonElectedCandidateList() = 0;
    // virtual Candidate* BreakTies(Candidate*, Candidate*) = 0;
};

#endif