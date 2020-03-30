
#ifndef BALLOT_H_
#define BALLOT_H_

#include <list>

class Ballot
{
private:
    int id_;
    // std::list<int> rankedCandidateIDList_;
public:
    Ballot() : id_(0) {};
    Ballot(int, int*);
    int GetId();
    std::list<int> GetRankedCandidateList();
    Ballot* operator = (Ballot *c) 
    { 
        return this; 
    }  
};

#endif