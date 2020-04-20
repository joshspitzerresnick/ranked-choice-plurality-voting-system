/**
 * @file candidate.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <stdlib.h>
#include "plurality_election_record.h"
#include "logger.h"

PluralityElectionRecord::PluralityElectionRecord(std::list<Candidate*> candidates, std::list<Ballot*> ballots) {
    this->nonDistributedBallotList_ = ballots;
    this->nonElectedCandidateList_ = candidates;
    this->winnersList_ = {};
    this->losersList_ = {};
}

void PluralityElectionRecord::DistributeBallots() {
    Ballot* curr_ballot;
    int curr_candidate_id;
    char msg[1000];
    while (!nonDistributedBallotList_.empty()) {
        curr_ballot = nonDistributedBallotList_.front();
        curr_candidate_id = curr_ballot->GetRankedCandidateIDList().front();
        std::list<Candidate*>::iterator it;
        for(it = this->nonElectedCandidateList_.begin(); it != this->nonElectedCandidateList_.end(); it++)
        {
            if((*it)->GetID() == curr_candidate_id)
            {
                (*it)->AddBallot(curr_ballot);
                snprintf(msg, sizeof(msg), "Ballot %d is assigned to Candidate %d-%s", curr_ballot->GetID(), (*it)->GetID(), (*it)->GetName().c_str());
                LOGGER->Log(msg);
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
    char msg[1000];
    srand(time(0));
    if(candidate1->GetNumBallots()  == candidate2->GetNumBallots())
    {
        bool select = rand() % 2;
        snprintf(msg, sizeof(msg), "Tie break between candidate %s (#votes=%d) and candidate %s (#votes=%d).",
        candidate1->GetName().c_str(), candidate1->GetNumBallots(), candidate2->GetName().c_str(), candidate2->GetNumBallots());
        LOGGER->Log(msg);
        if (select) {
           snprintf(msg, sizeof(msg), "candidate %s (#votes=%d) is randomly picked as the winner.",
           candidate1->GetName().c_str(), candidate1->GetNumBallots());
           LOGGER->Log(msg);
        } else {
           snprintf(msg, sizeof(msg), "candidate %s (#votes=%d) is randomly picked as the winner.",
           candidate2->GetName().c_str(), candidate2->GetNumBallots());
           LOGGER->Log(msg);
        }
        return select;
    }
    else
    {
        return candidate1->GetNumBallots() > candidate2->GetNumBallots();
    }
    

}

