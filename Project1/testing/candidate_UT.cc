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
    EXPECT_ANY_THROW(candidate1 = new Candidate(-1, "Mary", "Rep"));
    EXPECT_NO_THROW(candidate1 = new Candidate(1, "Mary", "Rep"));
    EXPECT_NO_THROW(candidate2 = new Candidate(2, "Mark", "Ind"));
    // Add more tests
}

TEST_F(CandidateTests, GetID) {
    EXPECT_EQ(candidate1->GetID(), 1);
    EXPECT_EQ(candidate2->GetID(), 2);
    candidate2 = new Candidate(43, "David", "Dem");
    EXPECT_EQ(candidate2->GetID(), 43);
}

TEST_F(CandidateTests, GetName) {
    EXPECT_EQ(candidate1->GetName(), "Allison");
    EXPECT_EQ(candidate2->GetName(), "Mark");
}

TEST_F(CandidateTests, GetNumBallots) {
    EXPECT_EQ(candidate1->GetNumBallots(), 0);
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
}

TEST_F(CandidateTests, AddBallot) {
    EXPECT_EQ(candidate1->GetNumBallots(), 0);
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    candidate1->AddBallot(ballot1);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    candidate2->AddBallot(ballot2);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate2->GetNumBallots(), 1);
    candidate2->AddBallot(ballot1);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate2->GetNumBallots(), 1);
}

TEST_F(CandidateTests, IncrementNumBallots) {
    EXPECT_EQ(candidate1->GetNumBallots(), 0);
    candidate1->AddBallot(ballot1);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    candidate2->AddBallot(ballot2);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
}

TEST_F(STVCandidateTests, Constructor) {
    EXPECT_ANY_THROW(candidate1 = new STVCandidate(-1, "Mary", "Rep"));
    EXPECT_NO_THROW(candidate1 = new STVCandidate(1, "Mary", "Rep"));
    EXPECT_NO_THROW(candidate2 = new STVCandidate(2, "Mark", "Ind"));
    // Add more tests
}

TEST_F(STVCandidateTests, AddBallot) {
    EXPECT_EQ(candidate1->GetNumBallots(), 0);
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    EXPECT_EQ(candidate1->GetFirstBallotNum(), 0);
    EXPECT_EQ(candidate2->GetFirstBallotNum(), 0);
    candidate1->AddBallot(ballot1);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    EXPECT_EQ(candidate1->GetFirstBallotNum(), 1);
    EXPECT_EQ(candidate2->GetFirstBallotNum(), 0);
    candidate2->AddBallot(ballot2);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate2->GetNumBallots(), 1);
    EXPECT_EQ(candidate1->GetFirstBallotNum(), 1);
    EXPECT_EQ(candidate2->GetFirstBallotNum(), 2);
    candidate2->AddBallot(ballot1);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate2->GetNumBallots(), 1);
    EXPECT_EQ(candidate1->GetFirstBallotNum(), 1);
    EXPECT_EQ(candidate2->GetFirstBallotNum(), 2);
}

TEST_F(STVCandidateTests, RemoveBallotList) {
    EXPECT_EQ(candidate1->GetNumBallots(), 0);
    EXPECT_EQ(candidate1->RemoveBallotList(), std::list<Ballot*>{});
    candidate1->AddBallot(ballot1);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate1->RemoveBallotList().front(), ballot1);
    candidate1->AddBallot(ballot2);
    EXPECT_EQ(candidate1->GetNumBallots(), 1);
    EXPECT_EQ(candidate1->RemoveBallotList().back(), ballot2);
    candidate1->AddBallot(ballot1);
    candidate1->AddBallot(ballot2);
    EXPECT_EQ(candidate1->RemoveBallotList().size(), 2);
}

TEST_F(STVCandidateTests, SetFirstBallotNum) {
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    EXPECT_NO_THROW(candidate2->SetFirstBallotNum(1));
    EXPECT_ANY_THROW(candidate2->SetFirstBallotNum(-1));
}

TEST_F(STVCandidateTests, GetFirstBallotNum) {
    EXPECT_EQ(candidate2->GetFirstBallotNum(), 0);
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    candidate2->SetFirstBallotNum(1);
    EXPECT_EQ(candidate2->GetFirstBallotNum(), 1);
    candidate2->SetFirstBallotNum(200);
    EXPECT_EQ(candidate2->GetFirstBallotNum(), 200);
}

TEST_F(STVCandidateTests, SetNumBallotZero) {
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    candidate2->AddBallot(ballot1);
    EXPECT_EQ(candidate2->GetNumBallots(), 1);
    candidate2->RemoveBallotList();
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
    candidate2->AddBallot(ballot1);
    candidate2->AddBallot(ballot2);
    EXPECT_EQ(candidate2->GetNumBallots(), 2);
    candidate2->RemoveBallotList();
    EXPECT_EQ(candidate2->GetNumBallots(), 0);
}
