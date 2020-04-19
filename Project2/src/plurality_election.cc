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
#include "logger.h"
//#include "plurality_election_record.cc"

PluralityElection::PluralityElection() {
}

void PluralityElection::RunElection(VotingInfo* votingInfo) {
    std::list<Candidate*> candidates_list = votingInfo->GetCandidateList();
    std::list<Ballot*> ballots_list = votingInfo->GetBallotList();
    int num_seats = votingInfo->GetNumSeats() <= votingInfo->GetNumCandidates() ? votingInfo->GetNumSeats() : votingInfo->GetNumCandidates();
    char msg[1000], temp[50];
    PluralityElectionRecord* election_record = new PluralityElectionRecord(candidates_list, ballots_list);
    snprintf(msg, sizeof(msg), "Start distributing %d ballots", votingInfo->GetNumBallots());
    LOGGER->Log(msg);
    election_record->DistributeBallots();
    election_record->SortNonElectedCandidateList();
    std::list<Candidate*> tempSTVCandidateList = election_record->GetNonElectedCandidateList();
    snprintf(msg, sizeof(msg), "Sorted nonElectedCandidateList: ");
    // Create an iterator of std::list
    std::list<Candidate*>::iterator itCandidate;
    for (itCandidate = tempSTVCandidateList.begin(); itCandidate != tempSTVCandidateList.end(); itCandidate++) {
      // Access the object through iterator
      snprintf(temp, sizeof(temp), "%s (%d votes), ", (*itCandidate)->GetName().c_str(), (*itCandidate)->GetNumBallots());
      strncat(msg, temp, sizeof(msg));
    }
    LOGGER->Log(msg);  // Log
    election_record->MoveFirstNCandidatesFromNonELectedListToWinnersList(num_seats);
    snprintf(msg, sizeof(msg), "Move the first %d candidates to winners list and the rest to losers list", num_seats);
    LOGGER->Log(msg);
    election_record->MoveRemainingCandidatesToLosersList();
    Logger::GetLogger()->Log("----------------------------------Election Complete----------------------------------------------------");
    DisplayResults(election_record, votingInfo);
}

void PluralityElection::DisplayResults(PluralityElectionRecord* election_record, VotingInfo* voting_info) {
    
    int num_ballots = voting_info->GetNumBallots();
    int num_seats = voting_info->GetNumSeats();
    int num_candidates = voting_info->GetNumCandidates();
    std::cout << "---------------Election Result-----------------\n" << std::flush;
    std::cout << "Election Type: Plurality\n" << std::flush;
    std::cout << "Number of Ballots: " << num_ballots << "\n" << std::flush;
    std::cout << "Number of Seats: " << num_seats << "\n" << std::flush;
    std::cout << "number of Candidates: " << num_candidates << "\n\n" << std::flush;

    std::list<Candidate*> winners_list = election_record->GetWinnersList();
    std::list<Candidate*> losers_list = election_record->GetLosersList();

    std::cout << "Winners are: \n" << std::flush;

    int i = 1;
    float percent;
    int candidate_num_ballots;
    Candidate* current_candidate;
    while(!winners_list.empty()) {
        current_candidate = winners_list.front();
        candidate_num_ballots = current_candidate->GetNumBallots();
        percent = (float)candidate_num_ballots / (float)num_ballots;
        percent = percent*100;
        std::cout << i << ". " << current_candidate->GetName() << " (" << candidate_num_ballots << " ballots; " << percent << "% Votes)\n" << std::flush;
        winners_list.pop_front();
        i++;
    }

    std::cout << "Losers are: \n" << std::flush;
    while(!losers_list.empty()) {
        current_candidate = losers_list.front();
        candidate_num_ballots = current_candidate->GetNumBallots();
        percent = (float)candidate_num_ballots / (float)num_ballots;
        percent = percent*100;
        std::cout << i << ". " << current_candidate->GetName() << " (" << candidate_num_ballots << " ballots; " << percent << "% Votes)\n" << std::flush;
        losers_list.pop_front(); 
        i++;
    }
}