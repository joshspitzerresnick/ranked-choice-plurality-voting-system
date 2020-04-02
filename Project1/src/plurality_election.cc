/**
 * @file plurality_election.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "plurality_election.h"
#include "plurality_election_record.h"
#include "voting_info.h"
#include "candidate.h"
#include "ballot.h"
//#include "plurality_election_record.cc"

PluralityElection::PluralityElection()
{

}

void PluralityElection::RunElection(VotingInfo* votingInfo)
{
    std::list<Candidate*> candidates_list = votingInfo->GetCandidateList();
    std::list<Ballot*> ballots_list = votingInfo->GetBallotList();
    int num_seats = votingInfo->GetNumSeats();

    PluralityElectionRecord* election_record = new PluralityElectionRecord(candidates_list, ballots_list);
    election_record->DistributeBallots();
    election_record->SortNonElectedCandidateList();
    election_record->MoveFirstNCandidatesFromNonELectedListToWinnersList(num_seats);
    election_record->MoveRemainingCandidatesToLosersList();
    

}

void PluralityElection::DisplayResults(PluralityElectionRecord* election_record, VotingInfo* voting_info)
{
    
    int num_ballots = voting_info->GetNumBallots();
    int num_seats = voting_info->GetNumSeats();
    int num_candidates = voting_info->GetNumCandidates();
    std::cout << "Election Type: Plurality" << std::endl;
    std::cout << "Number of Ballots: " << num_ballots << std::endl;
    std::cout << "Number of Seats: " << num_seats << std::endl;
    std::cout << "number of Candidates: " << num_candidates << std::endl << std::endl;

    std::list<Candidate*> winners_list = election_record->GetWinnersList();
    std::list<Candidate*> losers_list = election_record->GetWinnersList();

    std::cout << "Election Results:" << std::endl << std::endl;
    std::cout << "Winners list" << std::endl;
    std::cout << "Name    Number of votes" << std::endl;

    int i = 1;
    Candidate* current_candidate;
    while(!winners_list.empty())
    {    
        current_candidate = winners_list.front();
        std::cout << i << ". " << current_candidate->GetName() << "    " << current_candidate->GetNumBallots() << std::endl;
        winners_list.pop_front(); 
    }

    std::cout << "Losers list" << std::endl;
    std::cout << "Name    Number of votes" << std::endl;
    while(!losers_list.empty())
    {    
        current_candidate = losers_list.front();
        std::cout << i << ". " << current_candidate->GetName() << "    " << current_candidate->GetNumBallots() << std::endl;
        losers_list.pop_front(); 
    }
    
}