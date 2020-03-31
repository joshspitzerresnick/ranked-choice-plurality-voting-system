#include "ElectionRecord.h"
ElectionRecord::ElectionRecord() {};
// ElectionRecord::ElectionRecord(std::list<Ballot*> nonDistributedBallotList, std::list<Candidate*> nonElectedCandidateList) : 
//     nonDistributedBallotList_(nonDistributedBallotList), nonElectedCandidateList_(nonElectedCandidateList),
//     winnersList_{0}, losersList_{0} {}; 
// ElectionRecord::ElectionRecord(const ElectionRecord &){}; // copy constructor

// ElectionRecord::ElectionRecord & operator = (const ElectionRecord &){}; // copy operator

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