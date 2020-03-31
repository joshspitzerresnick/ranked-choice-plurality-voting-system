
#include "STVElectionRecord.h"

STVElectionRecord::STVElectionRecord() : DroopQuota_(0), discardedBallotList_(0)
{    
}

// STVElectionRecord::STVElectionRecord(std::list<STVCandidate> iniCandidateList, std::list<Ballot> iniBallotList, int DroopQuota) : 
//  ElectionRecord(iniBallotList, iniCandidateList), discardedBallotList_(0), DroopQuota_(DroopQuota)
// {
// }



std::list<Ballot*> STVElectionRecord::GetDiscardedBallotList()
{
    return discardedBallotList_;
};

int STVElectionRecord::GetDroopQuota()
{
    return DroopQuota_;
};

// void STVElectionRecord::ShuffleBallots()
// {
//     //to be implemented
// };

void STVElectionRecord::DistributeBallots()
{
    //to be implemented
};

bool STVElectionRecord::CheckDroop(int numBallots) {
    return ((numBallots>=DroopQuota_)?true:false);
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

std::list<Ballot*> STVElectionRecord::AddCandidateToLosersList(STVCandidate* candidate)
{
    //to be implemented
    auto ballots = std::list<Ballot*>(0);
    return ballots;
};

// void STVElectionRecord::AddLoserBallotsToNonDistributedBallotList(list<Ballot> ballotList)
// {
//     //to be implemented
// };

// void STVElectionRecord::AddBallotToDiscardedBallotList(Ballot* ballot)
// {
//     //to be implemented
// };

// STVCandidate* BreakTies(STVCandidate* candidate1, STVCandidate* candidate2)
// {
//     //to be implemented
//     return candidate1;
// };

// STVCandidate* STVElectionRecord::PopCandidateOffLosersList()
// {
//     //to be implemented
//     return nullptr;
// };

