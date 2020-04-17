/**
 * @file STVElectionRecord.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "stv_election_record.h"
#include <list>
#include <map>
#include "candidate.h"
#include "ballot.h"
#include <algorithm> //std::shuffle
#include <vector>
#include <cstdlib>
#include <random>  // std::default_random_engine
#include <chrono>  // std::chrono::system_clock

STVElectionRecord::STVElectionRecord(std::list<STVCandidate*> stvcandidate_list,std::list<Ballot*> ballot_list, int droop)
{
	this->nonDistributedBallotList_ = ballot_list;
	std::list<STVCandidate*>::iterator it;
	int curr_id = 0;
	for(it = stvcandidate_list.begin(); it != stvcandidate_list.end(); it++)
	{
		curr_id = (*it)->GetID();
		this->nonElectedCandidateMap.insert({curr_id,(*it)});

	}
	this->DroopQuota_ = droop;
	this->current_ballot_num = 1;

}

void STVElectionRecord::DistributeBallots()
{
	std::list<int> curr_candidate_id_list;
	int curr_candidate_id;
	Ballot* curr_ballot;
	STVCandidate* curr_candidate;
	while(!nonDistributedBallotList_.empty())
	{
		curr_ballot = nonDistributedBallotList_.front();
		nonDistributedBallotList_.pop_front();
		curr_candidate_id_list = curr_ballot->GetRankedCandidateIDList();
		while(!curr_candidate_id_list.empty())
		{
			curr_candidate_id = curr_candidate_id_list.front();
			curr_candidate_id_list.pop_front();
			curr_candidate = FindCandidate(curr_candidate_id);
			if(curr_candidate == NULL)
			{
				continue;
			}
			else
			{
				GiveBallotToCandidate(curr_ballot, curr_candidate, curr_candidate_id);
				break;
			}

		}


	}
}

STVCandidate* STVElectionRecord::FindCandidate(int candidate_num)
{
	if(this->nonElectedCandidateMap.find(candidate_num) == this->nonElectedCandidateMap.end())
	{
		return NULL;
	}
	else
	{
		return this->nonElectedCandidateMap[candidate_num];
	}
}

void STVElectionRecord::GiveBallotToCandidate(Ballot* ballot, STVCandidate* stvcandidate,int candidate_id)
{
	int current_votes;
	int first_ballot;
	first_ballot = stvcandidate->GetFirstBallotNum();
	if(first_ballot == 0)
	{
		stvcandidate->SetFirstBallotNum(this->current_ballot_num);
	}
	this->current_ballot_num++;
	current_votes = stvcandidate->AddBallot(ballot);
	if(CheckDroop(current_votes))
	{
		AddCandidateToWinnersList(stvcandidate);
		this->nonElectedCandidateMap.erase(candidate_id);


	}


}

bool STVElectionRecord::ValidCandidatesRemain()
{
	if(this->nonElectedCandidateMap.empty())
	{
		return false;
	}
	else
	{
		return true;
	}
}

// STVElectionRecord::~STVElectionRecord() {
//     // Add code here
// }

std::list<Ballot*> STVElectionRecord::GetNonDistributedBallotList()
{
  return nonDistributedBallotList_;
};

std::map<int,STVCandidate*> STVElectionRecord::GetNonElectedCandidateMap()
{
  return nonElectedCandidateMap;
};

std::list<STVCandidate*> STVElectionRecord::GetWinnersList()
{
  return winnersList_;
};

std::list<STVCandidate*> STVElectionRecord::GetLosersList()
{
  return losersList_;
};


void STVElectionRecord::ShuffleBallots() {

   std::vector<Ballot*> ballot_vector;
   std::copy(this->nonDistributedBallotList_.begin(), this->nonDistributedBallotList_.end(), std::back_inserter(ballot_vector));
   unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
   std::default_random_engine engine(seed);
   std::shuffle(ballot_vector.begin(), ballot_vector.end(), engine);
   std::shuffle(ballot_vector.begin(), ballot_vector.end(), engine);
   std::shuffle(ballot_vector.begin(), ballot_vector.end(), engine);
   this->nonDistributedBallotList_.clear();
   std::copy(ballot_vector.begin(), ballot_vector.end(), std::back_inserter(this->nonDistributedBallotList_));

}

bool STVElectionRecord::CheckDroop(int droop) {
  return ((droop >= DroopQuota_)? true:false);
}

void STVElectionRecord::AddCandidateToWinnersList(STVCandidate* candidate) {
  winnersList_.push_back(candidate);
}


void STVElectionRecord::AddCandidateToLosersList() {
	STVCandidate* loser;
	std::list<Ballot*> loser_ballots;
	loser = GetBiggestLoser();
	loser_ballots = loser->RemoveBallotList();
	std::list<Ballot*>::iterator it;
	for(it = loser_ballots.begin(); it != loser_ballots.end(); it++)
	{
		this->nonDistributedBallotList_.push_front((*it));

	}

	losersList_.push_back(loser);
	this->nonElectedCandidateMap.erase(loser->GetID());
}

STVCandidate* STVElectionRecord::GetBiggestLoser()
{
	std::map<int,STVCandidate*>::iterator it;
	std::list<STVCandidate*> loser_list = {};
	int min_ballots = this->DroopQuota_;
	int candidate_ballots;
	STVCandidate* loser_candidate;
	STVCandidate* curr_candidate;
	for(it = this->nonElectedCandidateMap.begin(); it != this->nonElectedCandidateMap.end(); it++)
	{
		curr_candidate = it->second;
		candidate_ballots = curr_candidate->GetNumBallots();
		if(candidate_ballots < min_ballots)
		{

			loser_list.clear();
			loser_list.push_front(curr_candidate);
			min_ballots = candidate_ballots;
		}
		else if(curr_candidate->GetNumBallots() == min_ballots)
		{
			loser_list.push_front(curr_candidate);
		}
	}
	if(loser_list.size() > 1)
	{
		loser_candidate = BreakLoserTie(loser_list);
	}
	else
	{
		loser_candidate = loser_list.front();
	}
	return loser_candidate;
}

STVCandidate* STVElectionRecord::BreakLoserTie(std::list<STVCandidate*> candidate_list)
{
	std::list<STVCandidate*>::iterator it;
	int last_ballot = 0;
	int current_candidate_first_ballot;
	STVCandidate* loser = candidate_list.front();
	for(it = candidate_list.begin(); it != candidate_list.end(); it++)
	{
		current_candidate_first_ballot = (*it)->GetFirstBallotNum();
		if(current_candidate_first_ballot > last_ballot)
		{
			last_ballot = current_candidate_first_ballot;
			loser = (*it);
		}
	}
	return loser;
}

void STVElectionRecord::FillWinnersList(int seats)
{
    STVCandidate* winner;
    while(this->winnersList_.size() < seats)
    {
    	winner = this->losersList_.back();
    	this->losersList_.pop_back();
    	this->winnersList_.push_back(winner);
    }
}




