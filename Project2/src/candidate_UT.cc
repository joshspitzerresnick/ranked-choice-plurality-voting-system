/**
 * @file candidate_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include <string>
#include "../src/candidate.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class CandidateTests : public ::testing::Test {
 protected:
  Ballot* ballot1;
  Ballot* ballot2;
  Candidate* candidate1;
  Candidate* candidate2;
  std::list<int> candidateList1, candidateList2, candidateDup;
  int i;
  virtual void SetUp() {
    for (i = 0; i < 5; i++) {
        candidateList1.push_back(i);
    }
    for (i = 0; i < 10; i++) {
        candidateList2.push_back(i);
    }
    for (i = 0; i < 5; i++) {
        candidateDup.push_back(i);
    }
    candidateDup.push_back(3);
    ballot1 = new Ballot(1, candidateList1);
    ballot2 = new Ballot(2, candidateList2);
    candidate1 = new Candidate(1, "Allison", "Democrat");
    candidate2 = new Candidate(2, "Mark", "Independant");
  }
  virtual void TearDown() {
    delete ballot1;
    delete ballot2;
    delete candidate1;
    delete candidate2;
  }
};

class STVCandidateTests : public ::testing::Test {
 protected:
  Ballot* ballot1;
  Ballot* ballot2;
  STVCandidate* candidate1;
  STVCandidate* candidate2;
  std::list<int> candidateList1, candidateList2, candidateDup;
  int i;
  virtual void SetUp() {
    for (i = 0; i < 5; i++) {
        candidateList1.push_back(i);
    }
    for (i = 0; i < 10; i++) {
        candidateList2.push_back(i);
    }
    for (i = 0; i < 5; i++) {
        candidateDup.push_back(i);
    }
    candidateDup.push_back(3);
    ballot1 = new Ballot(1, candidateList1);
    ballot2 = new Ballot(2, candidateList2);
    candidate1 = new STVCandidate(1, "Allison", "Democrat");
    candidate2 = new STVCandidate(2, "Mark", "Independant");
  }
  virtual void TearDown() {
    delete ballot1;
    delete ballot2;
    delete candidate1;
    delete candidate2;
  }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(CandidateTests, Constructor) {
    // Make sure exception is thrown for negative candidate id.
    EXPECT_ANY_THROW(candidate1 = new Candidate(-1, "Mary", "Rep"));
    // Check normal constructor.
    EXPECT_NO_THROW(candidate1 = new Candidate(1, "Mary", "Rep"));
    EXPECT_NO_THROW(candidate2 = new Candidate(2, "Mark", "Ind"));
}

TEST_F(CandidateTests, GetID) {
    // Check get candidate id normal operation.
    EXPECT_EQ(candidate1->GetID(), 1);
    EXPECT_EQ(candidate2->GetID(), 2);
    candidate2 = new Candidate(43, "David", "Dem");
    EXPECT_EQ(candidate2->GetID(), 43);
}

TEST_F(CandidateTests, GetName) {
    // Check get candidate name normal operation.
    EXPECT_EQ(candidate1->GetName(), "Allison");
    EXPECT_EQ(candidate2->GetName(), "Mark");
}

TEST_F(CandidateTests, GetNumBallots) {
    // Check get ballot count normal operation.
    EXPECT_EQ(candidate1->GetNumBallots(), 0);
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
}

TEST_F(CandidateTests, AddBallot) {
    // Check initial ballot count.
    EXPECT_EQ(candidate1->GetNumBallots(), 0);
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    // Add a ballot to candidate 1.
    candidate1->AddBallot(ballot1);
    // Check ballot counts.
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    // Add a ballot to candidate 2.
    candidate2->AddBallot(ballot2);
    // Check ballot counts.
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate2->GetNumBallots(), 1);
    // Add same ballot to candidate 1 and 2.
    candidate2->AddBallot(ballot1);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate2->GetNumBallots(), 1);
}

TEST_F(CandidateTests, IncrementNumBallots) {
    // Check initial ballot count.
    EXPECT_EQ(candidate1->GetNumBallots(), 0);
    // Add 1 ballot
    candidate1->AddBallot(ballot1);
    // Check count.
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    // Add another ballot
    candidate1->AddBallot(ballot2);
    // Check count.
    EXPECT_EQ(candidate1->GetNumBallots(), 2);
}

TEST_F(STVCandidateTests, Constructor) {
    // Make sure exception is thrown for negative candidate id.
    EXPECT_ANY_THROW(candidate1 = new STVCandidate(-1, "Mary", "Rep"));
    // Check normal construction.
    EXPECT_NO_THROW(candidate1 = new STVCandidate(1, "Mary", "Rep"));
    EXPECT_NO_THROW(candidate2 = new STVCandidate(2, "Mark", "Ind"));
    // Add more tests
}

TEST_F(STVCandidateTests, GetID) {
    // Check get stv candidate id normal operation.
    EXPECT_EQ(candidate1->GetID(), 1);
    EXPECT_EQ(candidate2->GetID(), 2);
    candidate2 = new STVCandidate(43, "David", "Dem");
    EXPECT_EQ(candidate2->GetID(), 43);
}

TEST_F(STVCandidateTests, GetName) {
    // Check get stv candidate name normal operation.
    EXPECT_EQ(candidate1->GetName(), "Allison");
    EXPECT_EQ(candidate2->GetName(), "Mark");
}

TEST_F(STVCandidateTests, GetNumBallots) {
    // Check get ballot count normal operation.
    EXPECT_EQ(candidate1->GetNumBallots(), 0);
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
}

TEST_F(STVCandidateTests, IncrementNumBallots) {
    // Check initial ballot count.
    EXPECT_EQ(candidate1->GetNumBallots(), 0);
    // Add 1 ballot
    candidate1->AddBallot(ballot1);
    // Check count.
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    // Add another ballot
    candidate1->AddBallot(ballot2);
    // Check count.
    EXPECT_EQ(candidate1->GetNumBallots(), 2);
}

TEST_F(STVCandidateTests, SetFirstBallotNum) {
    // Check that ballot count is zero.
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    // Try to set ballot num to a positive value.
    EXPECT_NO_THROW(candidate2->SetFirstBallotNum(1));
    // Try to set ballot num to a negative value.
    EXPECT_ANY_THROW(candidate2->SetFirstBallotNum(-1));
}

TEST_F(STVCandidateTests, GetFirstBallotNum) {
    // Check that first ballot num is zero.
    EXPECT_EQ(candidate2->GetFirstBallotNum(), 0);
    // Check initial ballot count.
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    // Set the first ballot num and check the value.
    candidate2->SetFirstBallotNum(1);
    EXPECT_EQ(candidate2->GetFirstBallotNum(), 1);
    // Set the first ballot num and check the value.
    candidate2->SetFirstBallotNum(200);
    EXPECT_EQ(candidate2->GetFirstBallotNum(), 200);
}

TEST_F(STVCandidateTests, AddBallot) {
    // Check initial ballot counts.
    EXPECT_EQ(candidate1->GetNumBallots(), 0);
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    // Check first ballot nums.
    EXPECT_EQ(candidate1->GetFirstBallotNum(), 0);
    EXPECT_EQ(candidate2->GetFirstBallotNum(), 0);
    // Add a ballot to candidate 1
    candidate1->AddBallot(ballot1);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    EXPECT_EQ(candidate1->GetFirstBallotNum(), 1);
    EXPECT_EQ(candidate2->GetFirstBallotNum(), 0);
    // Add a ballot to candidate 2
    candidate2->AddBallot(ballot2);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate2->GetNumBallots(), 1);
    EXPECT_EQ(candidate1->GetFirstBallotNum(), 1);
    EXPECT_EQ(candidate2->GetFirstBallotNum(), 2);
    // Add same ballot to candidate 1 and candidate 2
    candidate2->AddBallot(ballot1);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate2->GetNumBallots(), 1);
    EXPECT_EQ(candidate1->GetFirstBallotNum(), 1);
    EXPECT_EQ(candidate2->GetFirstBallotNum(), 2);
}

TEST_F(STVCandidateTests, RemoveBallotList) {
    // Check that initial list is null
    EXPECT_EQ(candidate1->GetNumBallots(), 0);
    EXPECT_EQ(candidate1->RemoveBallotList(), std::list<Ballot*>{});
    // Add a ballot to candidate 1 and check that it was added.
    candidate1->AddBallot(ballot1);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate1->RemoveBallotList().front(), ballot1);
    // Add another ballot to candidate 2 and check that is was added.
    candidate1->AddBallot(ballot2);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate1->RemoveBallotList().back(), ballot2);
    // Add the same ballots again and check that the ballot list is still 2.
    candidate1->AddBallot(ballot1);
    candidate1->AddBallot(ballot2);
    EXPECT_EQ(candidate1->RemoveBallotList().size(), 2);
}

TEST_F(STVCandidateTests, SetNumBallotZero) {
    // Check initial ballot count
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    // Add a ballot and check that it was added.
    candidate2->AddBallot(ballot1);
    EXPECT_EQ(candidate2->GetNumBallots(), 1);
    // Remove the ballot list (which sets ballot count to zero)
    candidate2->RemoveBallotList();
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    // Add two ballots check they were added, remove, and check.
    candidate2->AddBallot(ballot1);
    candidate2->AddBallot(ballot2);
    EXPECT_EQ(candidate2->GetNumBallots(), 2);
    candidate2->RemoveBallotList();
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
}
