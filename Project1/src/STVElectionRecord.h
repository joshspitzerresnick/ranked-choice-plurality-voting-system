
#ifndef STVELECTIONRECORD_H_
#define STVELECTIONRECORD_H_


#include "ElectionRecord.h"
#include "STVCandidate.h"
// #include "candidate.h"
// #include "ballot.h"
#include <list>
using namespace std;

class STVElectionRecord : public ElectionRecord
{
private:
    std::list<Ballot*> discardedBallotList_{};
    int DroopQuota_;
    // std::list<Ballot> nonDistributedBallotList_{};
    // std::list<STVCandidate> nonElectedCandidateList_{};
    // std::list<STVCandidate> winnersList_{};
    // std::list<STVCandidate> losersList_{};

public:
    STVElectionRecord();
    // STVElectionRecord() : nonDistributedBallotList_(0), nonElectedCandidateList_(0), winnersList_(0), losersList_(0), discardedBallotList_(0), DroopQuota_(0) {};
    // STVElectionRecord(std::list<STVCandidate> iniCandidateList, std::list<Ballot> iniBallotList, int DroopQuota);
    std::list<Ballot*> GetNonDistributedBallotList();
    std::list<Candidate*> GetNonElectedCandidateList();
    std::list<Candidate*> GetWinnersList();
    std::list<Candidate*> GetLosersList();
    std::list<Ballot*> GetDiscardedBallotList();
    int GetDroopQuota();
    // void ShuffleBallots();
    void DistributeBallots();
    bool CheckDroop(int);
    void AddCandidateToWinnersList(STVCandidate*);
    void SortNonElectedCandidateList();
    STVCandidate* RemoveLastCandidateFromNonElectedCandidateList();
    std::list<Ballot> AddCandidateToLosersList(STVCandidate*);
    // void AddLoserBallotsToNonDistributedBallotList(list<Ballot>);
    // void AddBallotToDiscardedBallotList(Ballot*);
    // Candidate* BreakTies(Candidate* candidate1, Candidate* candidate2);
    int* dummyf(int* i1, int* i2) {return i1;};
    // STVCandidate* PopCandidateOffLosersList();
};

#endif