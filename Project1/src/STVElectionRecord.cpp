
#include "STVElectionRecord.h"
/*
STVElectionRecord::STVElectionRecord() : _nonDistributedBallotList(0), _nonElectedCandidateList(0), _winnersList(0), _losersList(0), _discardedBallotLis(0), _DroopQuota(0)
{
    return;
}*/

STVElectionRecord::STVElectionRecord(std::list<STVCandidate> iniCandidateList, std::list<Ballot> iniBallotList, int DroopQuota)
{
    _nonDistributedBallotList(iniBallotList);
    _nonElectedCandidateList(iniCandidateList);
    _DroopQuota = DroopQuota;
}

std::list<Ballot> STVElectionRecord::GetNonDistributedBallotList()
{
    return _nonDistributedBallotList;
};

std::list<Candidate> STVElectionRecord::GetNonElectedCandidateList()
{
    return _nonElectedCandidateList;
};

std::list<Candidate> STVElectionRecord::GetWinnersList()
{
    return _winnersList;
};

std::list<Candidate> STVElectionRecord::GetLosersList()
{
    return _losersList;
};

std::list<Ballot> STVElectionRecord::GetDiscardedBallotList
{
    return _discardedBallotList;
};

int STVElectionRecord::GetDroopQuota()
{
    return _DroopQuota;
};

void STVElectionRecord::ShuffleBallots()
{
    //to be implemented
};

void STVElectionRecord::DistributeBallots()
{
    //to be implemented
};

bool STVElectionRecord::CheckDroop(int numBallots) {
    //to be implemented
    return true;
};

void STVElectionRecord::AddCandidateToWinnersList(STVCandidate* candidate)
{
    //to be implemented
};

void STVElectionRecord::SortNonElectedCandidateList()
{
    //to be implemented
};

STVCandidate* STVElectionRecord::RemoveLastCandidateFromNonElectedCandidateList()
{
    //to be implemented
    return nullptr;
};

std::list<Ballot> STVElectionRecord::AddCandidateToLosersList(STVCandidate* candidate)
{
    //to be implemented
    auto ballots = std::list<Ballot>(0);
    return ballots;
};

void STVElectionRecord::AddLoserBallotsToNonDistributedBallotList(list<Ballot> ballotList)
{
    //to be implemented
};

void STVElectionRecord::AddBallotToDiscardedBallotList(Ballot* ballot)
{
    //to be implemented
};

Candidate* STVElectionRecord::BreakTies(Candidate* candidate1, Candidate* candidate2)
{
    //to be implemented
    return nullptr;
};

STVCandidate* STVElectionRecord::PopCandidateOffLosersList()
{
    //to be implemented
    return nullptr;
};

