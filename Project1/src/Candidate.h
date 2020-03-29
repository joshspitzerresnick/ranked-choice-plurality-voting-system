
#ifndef CANDIDATE_H_
#define CANDIDATE_H_

#include <string>
#include <list>
#include "Ballot.h"
using namespace std;

class Candidate
{
protected:
    int id_;
    string name_;
    string party_;
    int numBallots_;
    list<Ballot> ballotList_;
public:
    Candidate() {};
    Candidate(int id, string name, string party) : id_(id), name_(name), party_(party) {};
    int GetId();
    string GetName();
    int IncrementNumBallots();
    int GetNumBallots();
    int AddBallot(Ballot*);
    Candidate* operator = (Candidate *c) 
    { 
        return this; 
    }  
};

#endif