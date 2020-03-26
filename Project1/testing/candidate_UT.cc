/**
 * @file candidate_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include "../src/candidate.cc"

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
    candidate1 = new Candidate(2, "Mark", "Independant");
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
    candidate1 = new STVCandidate(2, "Mark", "Independant");
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
    // Add tests
}

TEST_F(CandidateTests, GetName) {
    // Add tests
}

TEST_F(CandidateTests, GetNumBallots) {
    // Add tests
}

TEST_F(CandidateTests, AddBallot) {
    // Add tests
}

TEST_F(CandidateTests, IncrementNumBallots) {
    // Add tests
}

TEST_F(STVCandidateTests, Constructor) {
    // Add tests
}

TEST_F(STVCandidateTests, RemoveBallotList) {
    // Add tests
}

TEST_F(STVCandidateTests, SetFirstBallotNum) {
    // Add tests
}

TEST_F(STVCandidateTests, GetFirstBallotNum) {
    // Add tests
}

TEST_F(STVCandidateTests, SetNumBallotZero) {
    // Add tests
}
