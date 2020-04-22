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
  STVCandidate* candidate0;
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
  int droop;
virtual void SetUp() {
  candidate0 = new STVCandidate(0, "Billy", "left");
  candidate1 = new STVCandidate(1, "Al", "left");
  candidate2 = new STVCandidate(2, "Beth", "center");
  candidate3 = new STVCandidate(3, "Carl", "right");
  candidate4 = new STVCandidate(4, "Amy", "right");
  candidate5 = new STVCandidate(5, "Tim", "center");
  ballot1 = new Ballot(1, {0});
  ballot2 = new Ballot(2, {0});
  ballot3 = new Ballot(3, {0});
  ballot4 = new Ballot(4, {0});
  ballot5 = new Ballot(5, {0});
  candidates.push_front(candidate0);
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
  droop = 3;
  election_record = new STVElectionRecord(candidates, ballots, droop);
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
  EXPECT_NO_THROW(election_record = new STVElectionRecord(candidates,
                                                          ballots,
                                                          droop));
}

TEST_F(STVElectionRecordTests, DistributeBallots) {
  // Test distribute empty ballot list
  std::list<Ballot*> empty_ballots;
  std::list<Ballot*> ballot_list;
  int i;
  int firstBallotNum = 1;
  election_record = new STVElectionRecord(candidates, empty_ballots, 10);
  ballot_list = election_record->GetNonDistributedBallotList();
  EXPECT_EQ(ballot_list, empty_ballots);
  election_record->DistributeBallots(&firstBallotNum);
  ballot_list = election_record->GetNonDistributedBallotList();
  EXPECT_EQ(ballot_list, empty_ballots);
  std::list<STVCandidate*>::iterator itCandidate;
  for (itCandidate = candidates.begin();
      itCandidate != candidates.end(); itCandidate++) {
    EXPECT_EQ((*itCandidate)->GetNumBallots(), 0);
  }
  EXPECT_EQ(election_record->GetWinnersList(), std::list<STVCandidate*> {});

  // Test distribute 1 ballot, not meeting droop, no winner
  ballot_list.push_front(ballot1);
  election_record = new STVElectionRecord(candidates, ballot_list, 10);
  EXPECT_EQ(election_record->GetNonDistributedBallotList(), ballot_list);
  election_record->DistributeBallots(&firstBallotNum);
  ballot_list = election_record->GetNonDistributedBallotList();
  EXPECT_EQ(ballot_list, empty_ballots);
  for (itCandidate = candidates.begin();
      itCandidate != candidates.end(); itCandidate++) {
    if ((*itCandidate)->GetID() == 0) {
      EXPECT_EQ((*itCandidate)->GetNumBallots(), 1);
    } else {
      EXPECT_EQ((*itCandidate)->GetNumBallots(), 0);
    }
  }
  EXPECT_EQ(election_record->GetWinnersList(), std::list<STVCandidate*> {});

  // Test distribute 5 ballots, meet droop, 1 winner
  candidate0 = new STVCandidate(0, "Billy", "left");
  election_record = new STVElectionRecord(candidates, ballots, 2);
  EXPECT_EQ(election_record->GetNonDistributedBallotList(), ballots);
  election_record->DistributeBallots(&firstBallotNum);
  ballot_list = election_record->GetNonDistributedBallotList();
  EXPECT_EQ(ballot_list, empty_ballots);
  for (itCandidate = candidates.begin();
      itCandidate != candidates.end(); itCandidate++) {
    if ((*itCandidate)->GetID() == 0) {
      EXPECT_EQ((*itCandidate)->GetNumBallots(), 2);
    } else {
      EXPECT_EQ((*itCandidate)->GetNumBallots(), 0);
    }
  }
  std::list<STVCandidate*> winners;
  winners = election_record->GetWinnersList();
  EXPECT_EQ(winners.front()->GetName(), "Billy");
}

TEST_F(STVElectionRecordTests, SortNonElectedCandidateList) {
  std::list<STVCandidate*> candidates;
  std::list<Ballot*> ballots;
  candidate0 = new STVCandidate(0, "Billy", "left");
  candidate1 = new STVCandidate(1, "Al", "left");
  candidate2 = new STVCandidate(2, "Beth", "center");
  candidate3 = new STVCandidate(3, "Carl", "right");
  candidate4 = new STVCandidate(4, "Amy", "right");
  candidate5 = new STVCandidate(5, "Tim", "center");
  STVCandidate* test_candidate;
  ballot1 = new Ballot(1, {0});
  ballot2 = new Ballot(2, {0});
  ballot3 = new Ballot(3, {0});
  ballot4 = new Ballot(4, {0});
  ballot5 = new Ballot(5, {0});
  candidates.push_front(candidate0);
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
  int firstBallotNum = 1;
  std::list<STVCandidate*> candidate_list;
  election_record = new STVElectionRecord(candidates, ballots, 10);
  candidate_list = election_record->GetNonElectedCandidateList();
  EXPECT_EQ(candidate_list, candidates);
  election_record->SortNonElectedCandidateList();
  candidate_list = election_record->GetNonElectedCandidateList();
  EXPECT_EQ(candidate_list, candidates);
  election_record->DistributeBallots(&firstBallotNum);
  candidate_list = election_record->GetNonElectedCandidateList();
  EXPECT_EQ(candidate_list, candidates);
  test_candidate = candidate_list.front();
  EXPECT_EQ(test_candidate->GetName(), "Tim");
  election_record->SortNonElectedCandidateList();
  candidate_list = election_record->GetNonElectedCandidateList();
  EXPECT_NE(candidate_list, candidates);
  test_candidate = candidate_list.front();
  EXPECT_EQ(test_candidate->GetName(), "Billy");

  candidates.clear();
  ballots.clear();
  firstBallotNum = 1;
  candidate0 = new STVCandidate(0, "Billy", "left");
  candidate1 = new STVCandidate(1, "Al", "left");
  candidate2 = new STVCandidate(2, "Beth", "center");
  candidate3 = new STVCandidate(3, "Carl", "right");
  candidate4 = new STVCandidate(4, "Amy", "right");
  candidate5 = new STVCandidate(5, "Tim", "center");
  ballot1 = new Ballot(1, {0});
  ballot2 = new Ballot(2, {1});
  ballot3 = new Ballot(3, {1});
  ballot4 = new Ballot(4, {1});
  ballot5 = new Ballot(5, {2});
  candidates.push_front(candidate0);
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
  election_record = new STVElectionRecord(candidates, ballots, 10);
  election_record->DistributeBallots(&firstBallotNum);
  election_record->SortNonElectedCandidateList();
  candidate_list = election_record->GetNonElectedCandidateList();
  EXPECT_NE(candidate_list, candidates);
  test_candidate = candidate_list.front();
  EXPECT_EQ(test_candidate->GetName(), "Al");
  candidate_list.pop_front();
  test_candidate = candidate_list.front();
  EXPECT_EQ(test_candidate->GetName(), "Beth");
}

TEST_F(STVElectionRecordTests, GetWinnersList) {
  ASSERT_EQ(election_record->GetWinnersList(), std::list<STVCandidate*>{});
}

TEST_F(STVElectionRecordTests, AddCandidateToWinnersList) {
  ASSERT_EQ(election_record->GetWinnersList(), std::list<STVCandidate*>{});
  election_record->AddCandidateToWinnersList(candidate1);
  election_record->AddCandidateToWinnersList(candidate2);
  std::list<STVCandidate*> winners_list;
  winners_list = election_record->GetWinnersList();
  ASSERT_EQ(winners_list.size(), 2);
  ASSERT_EQ(winners_list.front(), candidate1);
  election_record->AddCandidateToWinnersList(candidate3);
  election_record->AddCandidateToWinnersList(candidate4);
  winners_list = election_record->GetWinnersList();
  ASSERT_EQ(winners_list.size(), 4);
  ASSERT_EQ(winners_list.front(), candidate1);
  winners_list.pop_front();
  ASSERT_EQ(winners_list.front(), candidate2);
  winners_list.pop_front();
  ASSERT_EQ(winners_list.front(), candidate3);
  winners_list.pop_front();
  ASSERT_EQ(winners_list.front(), candidate4);
}

TEST_F(STVElectionRecordTests, GetLosersList) {
  ASSERT_EQ(election_record->GetLosersList(), std::list<STVCandidate*>{});
}

TEST_F(STVElectionRecordTests, AddCandidateToLosersList) {
  ASSERT_EQ(election_record->GetLosersList(), std::list<STVCandidate*>{});
  election_record->AddCandidateToLosersList(candidate1);
  election_record->AddCandidateToLosersList(candidate2);
  std::list<STVCandidate*> losers_list;
  losers_list = election_record->GetLosersList();
  ASSERT_EQ(losers_list.size(), 2);
  ASSERT_EQ(losers_list.front(), candidate1);
  election_record->AddCandidateToLosersList(candidate3);
  election_record->AddCandidateToLosersList(candidate4);
  losers_list = election_record->GetLosersList();
  ASSERT_EQ(losers_list.size(), 4);
  ASSERT_EQ(losers_list.front(), candidate1);
  losers_list.pop_front();
  ASSERT_EQ(losers_list.front(), candidate2);
  losers_list.pop_front();
  ASSERT_EQ(losers_list.front(), candidate3);
  losers_list.pop_front();
  ASSERT_EQ(losers_list.front(), candidate4);
}

TEST_F(STVElectionRecordTests, GetNonElectedCandidateList) {
  ASSERT_EQ(election_record->GetNonElectedCandidateList(), candidates);
}

TEST_F(STVElectionRecordTests, GetNonDistributedBallotList) {
  ASSERT_EQ(election_record->GetNonDistributedBallotList(), ballots);
}

TEST_F(STVElectionRecordTests, ShuffleBallots) {
  std::list<Ballot*> ballot_list;
  ballot_list = election_record->GetNonDistributedBallotList();
  election_record->ShuffleBallots();
  std::list<Ballot*> shuffled_list;
  shuffled_list = election_record->GetNonDistributedBallotList();
  EXPECT_NE(shuffled_list, ballot_list);
}

TEST_F(STVElectionRecordTests, CheckDroop) {
  EXPECT_EQ(election_record->CheckDroop(2), false);
  EXPECT_EQ(election_record->CheckDroop(3), true);
  EXPECT_EQ(election_record->CheckDroop(4), true);
}

TEST_F(STVElectionRecordTests,
       RemoveLastCandidateFromNonElectedCandidateList) {
  std::list<STVCandidate*> candidate_test_list1;
  candidate_test_list1 = election_record->GetNonElectedCandidateList();
  STVCandidate* last_candidate_check1;
  last_candidate_check1 = election_record
                            ->RemoveLastCandidateFromNonElectedCandidateList();
  std::list<STVCandidate*> candidate_test_list2;
  candidate_test_list2 = election_record->GetNonElectedCandidateList();
  STVCandidate* last_candidate_check2;
  last_candidate_check2 = election_record
                            ->RemoveLastCandidateFromNonElectedCandidateList();
  EXPECT_EQ(candidate_test_list1.size(), candidates.size());
  EXPECT_EQ(candidate_test_list2.size(), candidates.size() - 1);
  EXPECT_EQ(last_candidate_check1, candidate0);
  EXPECT_EQ(last_candidate_check2, candidate1);
}

TEST_F(STVElectionRecordTests, AddLoserBallotsToNonDistributedBallotList) {
  std::list<Ballot*> ballot_list;
  ballot_list = election_record->GetNonDistributedBallotList();
  EXPECT_EQ(ballot_list, ballots);
  election_record->AddLoserBallotsToNonDistributedBallotList(ballots);
  ballot_list = election_record->GetNonDistributedBallotList();
  EXPECT_EQ(ballot_list.size(), ballots.size());
}

TEST_F(STVElectionRecordTests, PopCandidateOffLosersList) {
  EXPECT_EQ(election_record->GetLosersList().size(), 0);
  election_record->AddCandidateToLosersList(candidate1);
  EXPECT_EQ(election_record->GetLosersList().size(), 1);
  EXPECT_EQ(election_record->PopCandidateOffLosersList(), candidate1);
}
