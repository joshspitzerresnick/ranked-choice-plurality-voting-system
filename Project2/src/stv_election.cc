/**
 * @file stv_election.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "stv_election.h"
#include "stv_election_record.h"
// #include "voting_system.cc"
#include "voting_info.h"
#include <list>
#include "ballot.h"
#include <iostream>
#include <math.h>

STVElection::STVElection() {

}

void STVElection::RunElection(VotingInfo* votingInfo, bool ballot_shuffle){
    std::list<STVCandidate*> candidates_list = votingInfo->GetSTVCandidateList();
    std::list<Ballot*> ballots_list = votingInfo->GetBallotList();
    bool candidates_remain= true;
    float num_seats = (float)votingInfo->GetNumSeats();
    float num_ballots = (float)votingInfo->GetNumBallots();
    int droop = (int)floor(num_ballots / (num_seats + 1)) + 1;

    STVElectionRecord* election_record = new STVElectionRecord(candidates_list, ballots_list, droop);
    if(ballot_shuffle)
    {
        election_record->ShuffleBallots();
    }
    while(candidates_remain)
    {
        election_record->DistributeBallots();
        election_record->AddCandidateToLosersList();
        candidates_remain = election_record->ValidCandidatesRemain();
    }
    election_record->FillWinnersList((int)num_seats);
    DisplayResult(election_record, votingInfo);

}

void STVElection::DisplayResult(STVElectionRecord* stvElectionRecord,VotingInfo* votingInfo){

    int num_ballots = votingInfo->GetNumBallots();
    int num_seats = votingInfo->GetNumSeats();
    int num_candidates = votingInfo->GetNumCandidates();
    std::cout << "Election Type: STV\n" << std::flush;
    std::cout << "Number of Ballots: " << num_ballots << "\n" << std::flush;
    std::cout << "Number of Seats: " << num_seats << "\n" << std::flush;
    std::cout << "number of Candidates: " << num_candidates << "\n\n" << std::flush;

    std::list<STVCandidate*> winners_list = stvElectionRecord->GetWinnersList();
    std::list<STVCandidate*> losers_list = stvElectionRecord->GetLosersList();

    std::cout << "Election Results:\n\n" << std::flush;
    std::cout << "Winners list\n" << std::flush;
    std::cout << "Name  |  Number of votes |   percent\n" << std::flush;

    int i = 1;
    float percent;
    int candidate_num_ballots;
    STVCandidate* current_candidate;
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
