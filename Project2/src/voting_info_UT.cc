/**
 * @file voting_info_UT.cc
 *
 * @copyright 2020 Josh Spitzer-Resnick, spitz123
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/voting_info.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class VotingInfoTests : public ::testing::Test {
 protected:
  VotingInfo* votinginfo1;
  VotingInfo* votinginfo2;
  Candidate* candidate1;
  Candidate* candidate2;
  Candidate* candidate3;
  Ballot* ballot1;
  Ballot* ballot2;
  Ballot* ballot3;
  virtual void SetUp() {
    votinginfo1 = new VotingInfo(0, 3);  // plurality, 3 candidates
    votinginfo2 = new VotingInfo(1, 3);  // STV, 3 candidates
    candidate1 = new Candidate(1, "Al", "left");
    candidate2 = new Candidate(2, "Beth", "center");
    candidate3 = new Candidate(3, "Carl", "right");
    ballot1 = new Ballot(1, {1, 2, 3});
    ballot2 = new Ballot(2, {1, 3, 2});
    ballot3 = new Ballot(3, {1, 2});
  }
  virtual void TearDown() {
    delete votinginfo1;
    delete votinginfo2;
    delete candidate1;
    delete candidate2;
    delete candidate3;
    delete ballot1;
    delete ballot2;
    delete ballot3;
  }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(VotingInfoTests, Constructor) {
  EXPECT_EQ(votinginfo1->GetAlgorithm(), 0);
  EXPECT_EQ(votinginfo1->GetNumSeats(), 3);
  EXPECT_EQ(votinginfo1->GetNumCandidates(), 0);
  EXPECT_EQ(votinginfo1->GetNumBallots(), 0);
}

TEST_F(VotingInfoTests, GetAlgorithm) {
  EXPECT_EQ(votinginfo1->GetAlgorithm(), 0);
  EXPECT_EQ(votinginfo2->GetAlgorithm(), 1);
  EXPECT_NE(votinginfo1->GetAlgorithm(), -1);  // default value
}

TEST_F(VotingInfoTests, GetNumSeats) {
  EXPECT_EQ(votinginfo1->GetNumSeats(), 3);
  EXPECT_EQ(votinginfo2->GetNumSeats(), 3);
  EXPECT_NE(votinginfo1->GetNumSeats(), -1);  // default value
}

TEST_F(VotingInfoTests, AddCandidateToCandidateList) {
  EXPECT_EQ(votinginfo1->GetNumCandidates(), 0);
  votinginfo1->AddCandidateToCandidateList(candidate1);
  EXPECT_EQ(votinginfo1->GetNumCandidates(), 1);
  votinginfo1->AddCandidateToCandidateList(candidate2);
  EXPECT_EQ(votinginfo1->GetNumCandidates(), 2);
  votinginfo1->AddCandidateToCandidateList(candidate1);
  EXPECT_EQ(votinginfo1->GetNumCandidates(), 2);  // candidate1 already added
}

TEST_F(VotingInfoTests, AddBallotToBallotList) {
  EXPECT_EQ(votinginfo1->GetNumBallots(), 0);
  votinginfo1->AddBallotToBallotList(ballot1);
  EXPECT_EQ(votinginfo1->GetNumBallots(), 1);
  votinginfo1->AddBallotToBallotList(ballot2);
  EXPECT_EQ(votinginfo1->GetNumBallots(), 2);
  votinginfo1->AddBallotToBallotList(ballot1);
  EXPECT_EQ(votinginfo1->GetNumBallots(), 2);  // ballot1 already added
}

TEST_F(VotingInfoTests, GetNumCandidates) {
  EXPECT_EQ(votinginfo1->GetNumCandidates(), 0);
  EXPECT_EQ(votinginfo2->GetNumCandidates(), 0);
}

TEST_F(VotingInfoTests, GetNumBallots) {
  EXPECT_EQ(votinginfo1->GetNumBallots(), 0);
  EXPECT_EQ(votinginfo2->GetNumBallots(), 0);
}

TEST_F(VotingInfoTests, GetCandidateList) {
  EXPECT_EQ(votinginfo1->GetCandidateList(), std::list<Candidate*>{});
  votinginfo1->AddCandidateToCandidateList(candidate1);
  EXPECT_EQ(votinginfo1->GetCandidateList().front(), candidate1);
  votinginfo1->AddCandidateToCandidateList(candidate2);
  EXPECT_EQ(votinginfo1->GetCandidateList().back(), candidate2);  // in order
  EXPECT_EQ(votinginfo1->GetCandidateList().size(),
            votinginfo1->GetNumCandidates());
}

TEST_F(VotingInfoTests, GetBallotList) {
  EXPECT_EQ(votinginfo1->GetBallotList(), std::list<Ballot*>{});
  votinginfo1->AddBallotToBallotList(ballot1);
  EXPECT_EQ(votinginfo1->GetBallotList().front(), ballot1);
  votinginfo1->AddBallotToBallotList(ballot2);
  EXPECT_EQ(votinginfo1->GetBallotList().back(), ballot2);  // in order
  EXPECT_EQ(votinginfo1->GetBallotList().size(), votinginfo1->GetNumBallots());
}
