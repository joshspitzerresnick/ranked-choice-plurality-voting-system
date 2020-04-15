/**
 * @file candidate.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <stdlib.h>
#include "plurality_election_record.h"

PluralityElectionRecord::PluralityElectionRecord(std::list<Candidate*> candidates, std::list<Ballot*> ballots)
{
    this->nonDistributedBallotList_ = ballots;
    this->nonElectedCandidateList_ = candidates;
    this->winnersList_ = {};
    this->losersList_ = {};
}

void PluralityElectionRecord::DistributeBallots()
{

    Ballot* curr_ballot;
    int curr_candidate_id;
    while(!nonDistributedBallotList_.empty())
    {
        curr_ballot = nonDistributedBallotList_.front();
        curr_candidate_id = curr_ballot->GetRankedCandidateIDList().front();
        std::list<Candidate*>::iterator it;
        for(it = this->nonElectedCandidateList_.begin(); it != this->nonElectedCandidateList_.end(); it++)
        {
            if((*it)->GetID() == curr_candidate_id)
            {
                (*it)->AddBallot(curr_ballot);
                break;
            }
        }
        nonDistributedBallotList_.pop_front();



    }
}

void PluralityElectionRecord::SortNonElectedCandidateList()
{
    nonElectedCandidateList_.sort(CandidateNumBallotsComp);
}


bool PluralityElectionRecord::BreakTies()
{
    int rand_num = rand() % 2;
    if(rand_num == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
    
}

void PluralityElectionRecord::MoveFirstNCandidatesFromNonELectedListToWinnersList(int N)
{
    if(N > this->nonElectedCandidateList_.size())
    {
        throw 1;
    }   
    for(int i = 0; i < N; i++)
    {
        Candidate* temp_candidate = this->nonElectedCandidateList_.front();
        this->winnersList_.push_back(temp_candidate);
        this->nonElectedCandidateList_.pop_front();
    }
}

void PluralityElectionRecord::MoveRemainingCandidatesToLosersList()
{
    while(!this->nonElectedCandidateList_.empty())
    {
        Candidate* temp_candidate = this->nonElectedCandidateList_.front();
        this->losersList_.push_back(temp_candidate);
        this->nonElectedCandidateList_.pop_front();
    }
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


std::list<Ballot*> PluralityElectionRecord::GetNonDistributedBallotList()
{
    return this->nonDistributedBallotList_;
}

bool PluralityElectionRecord::CandidateNumBallotsComp(Candidate* candidate1, Candidate* candidate2)
{
    if(candidate1->GetNumBallots()  == candidate2->GetNumBallots())
    {
         return BreakTies();
    }
    else
    {
        return candidate1->GetNumBallots() > candidate2->GetNumBallots();
    }
    

}

