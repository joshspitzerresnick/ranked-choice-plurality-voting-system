/**
 * @file election.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "election.h"
#include "voting_info.h"
#include "result_display.h"
#include "election_record.h"

AbstractElection::AbstractElection() {
    // Add code here
}

void AbstractElection::RunElection(VotingInfo*) {
    // Add code here
}

PluralityElection::PluralityElection() {
    ResultDisplay displayResults;
    displayResults = new ResultDisplay();
    ResultDisplay = displayResults->PluralityResultDisplay();
}

void PluralityElection::RunElection(VotingInfo* votinginfo) {
    ResultDisplay displayResults;
    displayResults = new ResultDisplay();
    std::list<Candidate*> candidates_list = votinginfo->GetCandidateList();
    std::list<Ballot*> ballots_list = votinginfo->GetBallotList();
    int num_seats = votinginfo->GetNumSeats();
    ElectionRecord = new ElectionRecord::PluralityElectionRecord(candidates_list, ballots_list);
    ElectionRecord->DistributeBallots();
    ElectionRecord->SortNonElectedCandidateList();
    ElectionRecord->MoveFirstNCandidatesFromNonElectedListToWinnersList(num_seats);
    ElectionRecord->MoveFirstNCandidatesFromNonElectedListToLosersList(candidates_list.size());
    displayResults->DisplayElectionResults(ElectionRecord, votinginfo);
}

STVElection::STVElection() {
    // Add code here
}

void STVElection::RunElection(VotingInfo*) {
    // Add code here
}
