
#ifndef STVELECTIONRECORD_H_
#define STVELECTIONRECORD_H_


#include "ElectionRecord.h"
#include "Candidate.h"
#include "STVCandidate.h"
#include "Ballot.h"
// #include "STVCandidate.h"
// #include "candidate.h"
// #include "ballot.h"
#include <list>
using namespace std;

class STVElectionRecord : public ElectionRecord
{
private:
    std::list<Ballot*> discardedBallotList_{};
    int DroopQuota_;

public:
    STVElectionRecord();
    ~STVElectionRecord(){};
    // STVElectionRecord(std::list<STVCandidate> iniCandidateList, std::list<Ballot> iniBallotList, int DroopQuota);
    // std::list<Ballot*> GetNonDistributedBallotList();
    // std::list<Candidate*> GetNonElectedCandidateList();
    // std::list<Candidate*> GetWinnersList();
    // std::list<Candidate*> GetLosersList();
    std::list<Ballot*> GetDiscardedBallotList();
    int GetDroopQuota();
    // void ShuffleBallots();
    void DistributeBallots();
    bool CheckDroop(int);
    void AddCandidateToWinnersList(STVCandidate*);
    void SortNonElectedCandidateList();
    STVCandidate* RemoveLastCandidateFromNonElectedCandidateList();
    std::list<Ballot*> AddCandidateToLosersList(STVCandidate*);
    // void AddLoserBallotsToNonDistributedBallotList(list<Ballot>);
    void AddBallotToDiscardedBallotList(Ballot*) {};
    // Candidate* BreakTies(Candidate* candidate1, Candidate* candidate2) {return  candidate1;};
    STVCandidate* BreakTies(STVCandidate* candidate1, STVCandidate* candidate2) {return candidate1;};
    // STVCandidate* PopCandidateOffLosersList();
};

#endif