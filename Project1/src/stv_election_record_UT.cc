/**
 * @file candidate_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include "../src/stv_election_record.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class STVElectionRecordTests : public ::testing::Test {
 protected:
  STVCandidate* candidate1;
  STVCandidate* candidate2;
  STVCandidate* candidate3;
  STVCandidate* candidate4;
  STVCandidate* candidate5;
  Ballot* ballot1;
  Ballot* ballot2;
  Ballot* ballot3;
  Ballot* ballot4;
  Ballot* ballot5;
  std::list<STVCandidate*> candidates;
  std::list<Ballot*> ballots;
  STVElectionRecord* election_record;
virtual void SetUp() {
  candidate1 = new STVCandidate(1, "Al", "left");
  candidate2 = new STVCandidate(2, "Beth", "center");
  candidate3 = new STVCandidate(3, "Carl", "right");
  candidate4 = new STVCandidate(4, "Amy", "right");
  candidate5 = new STVCandidate(5, "Tim", "center");
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
  election_record = new STVElectionRecord(candidates, ballots);
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

TEST_F(STVElectionRecordTests, Constructor) {
  std::list<STVCandidate*> candidate_list;
  candidate_list = election_record->GetNonElectedCandidateList();
  std::list<Ballot*> ballot_list;
  ballot_list = election_record->GetNonDistributedBallotList();
  ASSERT_EQ(candidate_list, candidates);
  ASSERT_EQ(ballot_list, ballots);
}

TEST_F(STVElectionRecordTests, DistributeBallots) {
  election_record->DistributeBallots();
  std::list<Ballot*> ballot_list;
  ballot_list = election_record->GetNonDistributedBallotList();
  ASSERT_EQ(ballot_list, std::list<Ballot*>{});
  std::list<STVCandidate*> candidate_list;
  candidate_list = election_record->GetNonElectedCandidateList();
  ASSERT_EQ(candidate_list.size(), 5);
  std::list<STVCandidate*>::iterator it;
  for (it = candidate_list.begin();
       it != candidate_list.end(); it++) {
    if ((*it)->GetID() == 1) {
      ASSERT_EQ((*it)->GetNumBallots(), 3);
    } else if ((*it)->GetID() == 2) {
      ASSERT_EQ((*it)->GetNumBallots(), 2);
    } else {
      ASSERT_EQ((*it)->GetNumBallots(), 0);
    }
}
}

TEST_F(STVElectionRecordTests, SortNonElectedCandidateList) {
  election_record->DistributeBallots();
  election_record->SortNonElectedCandidateList();
  std::list<STVCandidate*> temp_candidate_list;
  temp_candidate_list = election_record->GetNonElectedCandidateList();
  STVCandidate* most_ballots = temp_candidate_list.front();
  ASSERT_EQ(most_ballots->GetID(), 1);
  temp_candidate_list.pop_front();
  most_ballots = temp_candidate_list.front();
  ASSERT_EQ(most_ballots->GetID(), 2);
}

TEST_F(STVElectionRecordTests, SortNonElectedCandidateList_reorder) {
  // same as the previous test, but we reorder the candidates to make
  // sure that the list is actually being sorted.
  STVCandidate* candidate1_reorder;
  STVCandidate* candidate2_reorder;
  STVCandidate* candidate3_reorder;
  STVCandidate* candidate4_reorder;
  STVCandidate* candidate5_reorder;
  Ballot* ballot1_reorder;
  Ballot* ballot2_reorder;
  Ballot* ballot3_reorder;
  Ballot* ballot4_reorder;
  Ballot* ballot5_reorder;
  std::list<STVCandidate*> candidates_reorder;
  std::list<Ballot*> ballots_reorder;
  STVElectionRecord* election_record_reorder;
  candidate1_reorder = new STVCandidate(1, "Al", "left");
  candidate2_reorder = new STVCandidate(2, "Beth", "center");
  candidate3_reorder = new STVCandidate(3, "Carl", "right");
  candidate4_reorder = new STVCandidate(4, "Amy", "right");
  candidate5_reorder = new STVCandidate(5, "Tim", "center");
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
  election_record_reorder = new STVElectionRecord(candidates_reorder,
                                                        ballots_reorder);
  election_record_reorder->DistributeBallots();
  election_record_reorder->SortNonElectedCandidateList();
  std::list<STVCandidate*> temp_candidate_list;
  temp_candidate_list = election_record_reorder->GetNonElectedCandidateList();
  STVCandidate* most_ballots = temp_candidate_list.front();
  ASSERT_EQ(most_ballots->GetID(), 5);
  temp_candidate_list.pop_front();
  most_ballots = temp_candidate_list.front();
  ASSERT_EQ((most_ballots->GetID() == 2) || (most_ballots->GetID() == 3), true);
}

TEST_F(STVElectionRecordTests, GetWinnersList) {
  ASSERT_EQ(election_record->GetWinnersList(), std::list<STVCandidate*>{});
  election_record->MoveFirstNCandidatesFromNonELectedListToWinnersList(2);
  std::list<STVCandidate*> winners_list = election_record->GetWinnersList();
  ASSERT_EQ(winners_list.size(), 2);
  ASSERT_EQ(winners_list.front(), candidate5);
  election_record->MoveFirstNCandidatesFromNonELectedListToWinnersList(2);
  winners_list = election_record->GetWinnersList();
  ASSERT_EQ(winners_list.size(), 4);
  ASSERT_EQ(winners_list.front(), candidate5);
  winners_list.pop_front();
  STVCandidate* winning_candidate = winners_list.front();
  ASSERT_EQ(winners_list.front(), candidate4);
  winners_list.pop_front();
  winning_candidate = winners_list.front();
  ASSERT_EQ(winners_list.front(), candidate3);
  winners_list.pop_front();
  winning_candidate = winners_list.front();
  ASSERT_EQ(winners_list.front(), candidate2);
}

TEST_F(STVElectionRecordTests, GetLosersList) {
  ASSERT_EQ(election_record->GetLosersList(), std::list<STVCandidate*>{});
  election_record->MoveFirstNCandidatesFromNonELectedListToWinnersList(2);
  election_record->MoveRemainingCandidatesToLosersList();
  std::list<STVCandidate*> losers_list = election_record->GetLosersList();
  ASSERT_EQ(losers_list.size(), 3);
  ASSERT_EQ(losers_list.front(), candidate3);
  losers_list.pop_front();
  STVCandidate* losing_candidate = losers_list.front();
  ASSERT_EQ(losing_candidate, candidate2);
  losers_list.pop_front();
  losing_candidate = losers_list.front();
  ASSERT_EQ(losing_candidate, candidate1);
}

TEST_F(STVElectionRecordTests, GetNonElectedCandidateList) {
  ASSERT_EQ(election_record->GetNonElectedCandidateList(), candidates);
}

TEST_F(STVElectionRecordTests, GetNonDistributedBallotList) {
  ASSERT_EQ(election_record->GetNonDistributedBallotList(), ballots);
}

