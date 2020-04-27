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
    DisplayResults(election_record, votingInfo);
    snprintf(msg, sizeof(msg), "---------------------------------------------------------Election Complete---------------------------------------------------------");
    Logger::GetLogger()->Log(msg);
}

void PluralityElection::DisplayResults(PluralityElectionRecord* election_record, VotingInfo* voting_info) {
    
    int num_ballots = voting_info->GetNumBallots();
    int num_seats = voting_info->GetNumSeats();
    int num_candidates = voting_info->GetNumCandidates();
    char msg[1000];
    snprintf(msg, sizeof(msg), "---------------Election Result----------------");
    LOGGER->Log(msg);
    std::cout << msg << "\n" << std::flush;
    snprintf(msg, sizeof(msg), "* Election Type: Plurality");
    LOGGER->Log(msg);
    std::cout << msg << std::endl;
    snprintf(msg, sizeof(msg), "* Number of Ballots: %d", num_ballots);
    LOGGER->Log(msg);
    std::cout << msg << std::endl;
    snprintf(msg, sizeof(msg), "* #Seats: %d", num_seats);
    LOGGER->Log(msg);
    std::cout << msg << std::endl;
    snprintf(msg, sizeof(msg), "* #Candidates: %d", num_candidates);
    LOGGER->Log(msg);
    std::cout << msg << std::endl;

    std::list<Candidate*> winners_list = election_record->GetWinnersList();
    std::list<Candidate*> losers_list = election_record->GetLosersList();

    snprintf(msg, sizeof(msg), "* Winners are: ");
    LOGGER->Log(msg);
    std::cout << msg << std::endl;

    int i = 1;
    float percent;
    int candidate_num_ballots;
    Candidate* current_candidate;
    while(!winners_list.empty()) {
        current_candidate = winners_list.front();
        candidate_num_ballots = current_candidate->GetNumBallots();
        percent = (float)candidate_num_ballots / (float)num_ballots;
        percent = percent*100;
        snprintf(msg, sizeof(msg), "  %d: %s (%d ballots; %%%.2f Votes)", 
                  i, current_candidate->GetName().c_str(), candidate_num_ballots, percent);
        LOGGER->Log(msg);
        std::cout << msg << "\n" << std::flush;
        winners_list.pop_front();
        i++;
    }

    snprintf(msg, sizeof(msg), "* Losers are: ");
    LOGGER->Log(msg);
    std::cout << msg << std::endl;
    while(!losers_list.empty()) {
        current_candidate = losers_list.front();
        candidate_num_ballots = current_candidate->GetNumBallots();
        percent = (float)candidate_num_ballots / (float)num_ballots;
        percent = percent*100;
        snprintf(msg, sizeof(msg), "  %d: %s (%d ballots; %%%.2f Votes)", 
                  i, current_candidate->GetName().c_str(), candidate_num_ballots, percent);
        LOGGER->Log(msg);
        std::cout << msg << "\n" << std::flush;
        // std::cout << i << ". " << current_candidate->GetName() << " (" << candidate_num_ballots << " ballots; " << percent << "% Votes)\n" << std::flush;
        losers_list.pop_front(); 
        i++;
    }
    snprintf(msg, sizeof(msg), "Location of audit report: \\src\\%s", LogFileName);
    LOGGER->Log(msg);
    std::cout << msg << "\n" << std::flush;
    snprintf(msg, sizeof(msg), "-------------End of Result Display------------");
    LOGGER->Log(msg);
    std::cout << msg << std::endl;
}
