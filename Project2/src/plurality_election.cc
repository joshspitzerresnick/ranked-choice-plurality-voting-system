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
    int num_seats = votingInfo->GetNumSeats() <= votingInfo->GetNumCandidates() ? votingInfo->GetNumSeats() : votingInfo->GetNumCandidates();

    PluralityElectionRecord* election_record = new PluralityElectionRecord(candidates_list, ballots_list);
    election_record->DistributeBallots();
    election_record->SortNonElectedCandidateList();
    election_record->MoveFirstNCandidatesFromNonELectedListToWinnersList(num_seats);
    election_record->MoveRemainingCandidatesToLosersList();
    DisplayResults(election_record, votingInfo);


}

void PluralityElection::DisplayResults(PluralityElectionRecord* election_record, VotingInfo* voting_info) {

    int num_ballots = voting_info->GetNumBallots();
    int num_seats = voting_info->GetNumSeats();
    int num_candidates = voting_info->GetNumCandidates();
    std::cout << "--------------------Election Results------------------------\n" << std::flush;
    std::cout << "* Election Type:\tPlurality\n" << std::flush;
    std::cout << "* # Ballots:\t\t" << num_ballots << "\n" << std::flush;
    std::cout << "* # Seats:\t\t" << num_seats << "\n" << std::flush;
    std::cout << "* # Candidates:\t\t" << num_candidates << "\n" << std::flush;

    std::list<Candidate*> winners_list = election_record->GetWinnersList();
    std::list<Candidate*> losers_list = election_record->GetLosersList();

    std::cout << "\n* Winners list:\n" << std::flush;
    std::cout << "Name\t# votes\t %\n" << std::flush;

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
        std::cout << i << ". " << current_candidate->GetName() << "\t " << candidate_num_ballots << "\t " << percent << "\n" << std::flush;
        winners_list.pop_front();
        i++;
    }

    std::cout << "\n* Losers list:\n" << std::flush;
    while(!losers_list.empty())
    {
        current_candidate = losers_list.front();
        candidate_num_ballots = current_candidate->GetNumBallots();
        percent = (float)candidate_num_ballots / (float)num_ballots;
        percent = percent*100;
        std::cout << i << ". " << current_candidate->GetName() << "\t " << candidate_num_ballots << "\t " << percent << "\n" << std::flush;
        losers_list.pop_front();
        i++;
    }
    std::cout << "\nLocation of audit report:\t\tsrc/audit.txt" << std::endl;
    std::cout << "--------------------End of Result Display-------------------" << std::endl;
}
