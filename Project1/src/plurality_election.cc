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
    DisplayResults(election_record, votingInfo);
    

}

void PluralityElection::DisplayResults(PluralityElectionRecord* election_record, VotingInfo* voting_info)
{
    
    int num_ballots = voting_info->GetNumBallots();
    int num_seats = voting_info->GetNumSeats();
    int num_candidates = voting_info->GetNumCandidates();
    std::cout << "Election Type: Plurality\n" << std::flush;
    std::cout << "Number of Ballots: " << num_ballots << "\n" << std::flush;
    std::cout << "Number of Seats: " << num_seats << "\n" << std::flush;
    std::cout << "number of Candidates: " << num_candidates << "\n\n" << std::flush;

    std::list<Candidate*> winners_list = election_record->GetWinnersList();
    std::list<Candidate*> losers_list = election_record->GetLosersList();

    std::cout << "Election Results:\n\n" << std::flush;
    std::cout << "Winners list\n" << std::flush;
    std::cout << "Name  |  Number of votes |   percent\n" << std::flush;

    int i = 1;
    float percent;
    int candidate_num_ballots;
    Candidate* current_candidate;
    while(!winners_list.empty())
    {    
        current_candidate = winners_list.front();
        candidate_num_ballots = current_candidate->GetNumBallots();
        percent = (float)candidate_num_ballots / (float)num_ballots;
        percent = percent*100;
        std::cout << i << ". " << current_candidate->GetName() << "    " << candidate_num_ballots << "    " << percent << "\n" << std::flush;
        winners_list.pop_front();
        i++;
    }
    
    std::cout << "Losers list\n\n" << std::flush;
    while(!losers_list.empty())
    {    
        current_candidate = losers_list.front();
        candidate_num_ballots = current_candidate->GetNumBallots();
        percent = (float)candidate_num_ballots / (float)num_ballots;
        percent = percent*100;
        std::cout << i << ". " << current_candidate->GetName() << "    " << candidate_num_ballots << "    " << percent << "\n" << std::flush;
        losers_list.pop_front(); 
        i++;
    }
    
}