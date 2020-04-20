/**
 * @file candidate_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include "../src/plurality_election_record.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class PluralityElectionRecordTests : public ::testing::Test {
 protected:
    Candidate* candidate1;
    Candidate* candidate2;
    Candidate* candidate3;
    Candidate* candidate4;
    Candidate* candidate5;
    Ballot* ballot1;
    Ballot* ballot2;
    Ballot* ballot3;
    Ballot* ballot4;
    Ballot* ballot5;
    std::list<Candidate*> candidates;
    std::list<Ballot*> ballots;
    PluralityElectionRecord* election_record;
  virtual void SetUp() {
    candidate1 = new Candidate(1, "Al", "left");
    candidate2 = new Candidate(2, "Beth", "center");
    candidate3 = new Candidate(3, "Carl", "right");
    candidate4 = new Candidate(4, "Amy", "right");
    candidate5 = new Candidate(5, "Tim", "center");
    ballot1 = new Ballot(1, {1});
    ballot2 = new Ballot(2, {1});
    ballot3 = new Ballot(3, {1});
    ballot4 = new Ballot(4, {2});
    ballot5 = new Ballot(5, {2});
    candidates.push_front(candidate1);
    candidates.push_front(candidate2);
    candidates.push_front(candidate3);
    candidates.push_front(candidate4);
    candidates.push_front(candidate5);
    ballots.push_front(ballot1);
    ballots.push_front(ballot2);
    ballots.push_front(ballot3);
    ballots.push_front(ballot4);
    ballots.push_front(ballot5);
    election_record = new PluralityElectionRecord(candidates, ballots);
  }
  virtual void TearDown() {
    delete candidate1;
    delete candidate2;
    delete candidate3;
    delete candidate4;
    delete candidate5;
    delete ballot1;
    delete ballot2;
    delete ballot3;
    delete ballot4;
    delete ballot5;
  }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(PluralityElectionRecordTests, Constructor) {
  std::list<Candidate*> candidate_list;
  candidate_list = election_record->GetNonElectedCandidateList();
  std::list<Ballot*> ballot_list;
  ballot_list = election_record->GetNonDistributedBallotList();
  ASSERT_EQ(candidate_list, candidates);
  ASSERT_EQ(ballot_list, ballots);
}

TEST_F(PluralityElectionRecordTests, DistributeBallots) {
  election_record->DistributeBallots();
  std::list<Ballot*> ballot_list;
  ballot_list = election_record->GetNonDistributedBallotList();
  ASSERT_EQ(ballot_list, std::list<Ballot*>{});
  std::list<Candidate*> candidate_list;
  candidate_list = election_record->GetNonElectedCandidateList();
  ASSERT_EQ(candidate_list.size(), 5);
  std::list<Candidate*>::iterator it;
  for (it = candidate_list.begin(); it != candidate_list.end(); it++) {
    if ((*it)->GetID() == 1) {
      ASSERT_EQ((*it)->GetNumBallots(), 3);
    } else if ((*it)->GetID() == 2) {
      ASSERT_EQ((*it)->GetNumBallots(), 2);
    } else {
      ASSERT_EQ((*it)->GetNumBallots(), 0);
    }
  }
}

TEST_F(PluralityElectionRecordTests, SortNonElectedCandidateList) {
  election_record->DistributeBallots();
  election_record->SortNonElectedCandidateList();
  std::list<Candidate*> temp_candidate_list;
  temp_candidate_list = election_record->GetNonElectedCandidateList();
  Candidate* most_ballots = temp_candidate_list.front();
  ASSERT_EQ(most_ballots->GetID(), 1);
  temp_candidate_list.pop_front();
  most_ballots = temp_candidate_list.front();
  ASSERT_EQ(most_ballots->GetID(), 2);
}

TEST_F(PluralityElectionRecordTests, SortNonElectedCandidateList_reorder) {
  // same as the previous test, but we reorder the candidates to make
  // sure that the list is actually being sorted.
  Candidate* candidate1_reorder;
  Candidate* candidate2_reorder;
  Candidate* candidate3_reorder;
  Candidate* candidate4_reorder;
  Candidate* candidate5_reorder;
  Ballot* ballot1_reorder;
  Ballot* ballot2_reorder;
  Ballot* ballot3_reorder;
  Ballot* ballot4_reorder;
  Ballot* ballot5_reorder;
  std::list<Candidate*> candidates_reorder;
  std::list<Ballot*> ballots_reorder;
  PluralityElectionRecord* election_record_reorder;
  candidate1_reorder = new Candidate(1, "Al", "left");
  candidate2_reorder = new Candidate(2, "Beth", "center");
  candidate3_reorder = new Candidate(3, "Carl", "right");
  candidate4_reorder = new Candidate(4, "Amy", "right");
  candidate5_reorder = new Candidate(5, "Tim", "center");
  ballot1_reorder = new Ballot(1, {2});
  ballot2_reorder = new Ballot(2, {3});
  ballot3_reorder = new Ballot(3, {5});
  ballot4_reorder = new Ballot(4, {5});
  ballot5_reorder = new Ballot(5, {5});
  candidates_reorder.push_front(candidate2_reorder);
  candidates_reorder.push_front(candidate1_reorder);
  candidates_reorder.push_front(candidate5_reorder);
  candidates_reorder.push_front(candidate4_reorder);
  candidates_reorder.push_front(candidate3_reorder);
  ballots_reorder.push_front(ballot2_reorder);
  ballots_reorder.push_front(ballot1_reorder);
  ballots_reorder.push_front(ballot5_reorder);
  ballots_reorder.push_front(ballot4_reorder);
  ballots_reorder.push_front(ballot3_reorder);
  election_record_reorder = new PluralityElectionRecord(candidates_reorder,
                                                        ballots_reorder);
  election_record_reorder->DistributeBallots();
  election_record_reorder->SortNonElectedCandidateList();
  std::list<Candidate*> temp_candidate_list;
  temp_candidate_list = election_record_reorder->GetNonElectedCandidateList();
  Candidate* most_ballots = temp_candidate_list.front();
  ASSERT_EQ(most_ballots->GetID(), 5);
  temp_candidate_list.pop_front();
  most_ballots = temp_candidate_list.front();
  ASSERT_EQ((most_ballots->GetID() == 2) || (most_ballots->GetID() == 3), true);
}

TEST_F(PluralityElectionRecordTests,
       MoveFirstNCandidatesFromNonElectedListToWinnersList) {
  ASSERT_ANY_THROW(election_record
                     ->MoveFirstNCandidatesFromNonELectedListToWinnersList(20));
  election_record->MoveFirstNCandidatesFromNonELectedListToWinnersList(3);
  std::list<Candidate*> candidates_list = election_record->GetWinnersList();
  Candidate* Candidate_first = candidates_list.front();
  ASSERT_EQ(Candidate_first, candidate5);
  candidates_list.pop_front();
  Candidate_first = candidates_list.front();
  ASSERT_EQ(Candidate_first, candidate4);
  candidates_list.pop_front();
  Candidate_first = candidates_list.front();
  ASSERT_EQ(Candidate_first, candidate3);
}

TEST_F(PluralityElectionRecordTests, MoveRemainingCandidatesToLosersList) {
  election_record->MoveFirstNCandidatesFromNonELectedListToWinnersList(2);
  election_record->MoveRemainingCandidatesToLosersList();
  std::list<Candidate*> losers_list = election_record->GetLosersList();
  ASSERT_EQ(losers_list.size(), 3);
  Candidate* first_loser = losers_list.front();
  ASSERT_EQ(first_loser, candidate3);
  losers_list.pop_front();
  first_loser = losers_list.front();
  ASSERT_EQ(first_loser, candidate2);
  losers_list.pop_front();
  first_loser = losers_list.front();
  ASSERT_EQ(first_loser, candidate1);
}

TEST_F(PluralityElectionRecordTests, GetWinnersList) {
  ASSERT_EQ(election_record->GetWinnersList(), std::list<Candidate*>{});
  election_record->MoveFirstNCandidatesFromNonELectedListToWinnersList(2);
  std::list<Candidate*> winners_list = election_record->GetWinnersList();
  ASSERT_EQ(winners_list.size(), 2);
  ASSERT_EQ(winners_list.front(), candidate5);
  election_record->MoveFirstNCandidatesFromNonELectedListToWinnersList(2);
  winners_list = election_record->GetWinnersList();
  ASSERT_EQ(winners_list.size(), 4);
  ASSERT_EQ(winners_list.front(), candidate5);
  winners_list.pop_front();
  Candidate* winning_candidate = winners_list.front();
  ASSERT_EQ(winners_list.front(), candidate4);
  winners_list.pop_front();
  winning_candidate = winners_list.front();
  ASSERT_EQ(winners_list.front(), candidate3);
  winners_list.pop_front();
  winning_candidate = winners_list.front();
  ASSERT_EQ(winners_list.front(), candidate2);
}

TEST_F(PluralityElectionRecordTests, GetLosersList) {
  ASSERT_EQ(election_record->GetLosersList(), std::list<Candidate*>{});
  election_record->MoveFirstNCandidatesFromNonELectedListToWinnersList(2);
  election_record->MoveRemainingCandidatesToLosersList();
  std::list<Candidate*> losers_list = election_record->GetLosersList();
  ASSERT_EQ(losers_list.size(), 3);
  ASSERT_EQ(losers_list.front(), candidate3);
  losers_list.pop_front();
  Candidate* losing_candidate = losers_list.front();
  ASSERT_EQ(losing_candidate, candidate2);
  losers_list.pop_front();
  losing_candidate = losers_list.front();
  ASSERT_EQ(losing_candidate, candidate1);
}

TEST_F(PluralityElectionRecordTests, GetNonElectedCandidateList) {
    ASSERT_EQ(election_record->GetNonElectedCandidateList(), candidates);
}

TEST_F(PluralityElectionRecordTests, GetNonDistributedBallotList) {
    ASSERT_EQ(election_record->GetNonDistributedBallotList(), ballots);
}
