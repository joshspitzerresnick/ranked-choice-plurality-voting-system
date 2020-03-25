/**
 * @file ballot_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include "../src/ballot.cc"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class BallotTests : public ::testing::Test {
 protected:
  Ballot* ballot1;
  Ballot* ballot2;
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
  }
  virtual void TearDown() {
    delete ballot1;
    delete ballot2;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(BallotTests, Constructor) {
    EXPECT_ANY_THROW(ballot1 = new Ballot(-1, candidateList1));
    EXPECT_ANY_THROW(ballot1 = new Ballot(1, candidateDup));
    EXPECT_NO_THROW(ballot1 = new Ballot(1, candidateList1));
    EXPECT_NO_THROW(ballot2 = new Ballot(2, candidateList2));
}

TEST_F(BallotTests, GetID) {
    EXPECT_EQ(ballot1->GetID(), 1);
    EXPECT_EQ(ballot2->GetID(), 2);
}

TEST_F(BallotTests, GetRankedCandidateList) {
    EXPECT_EQ(ballot1->GetRankedCandidateIDList(), candidateList1);
    EXPECT_EQ(ballot2->GetRankedCandidateIDList(), candidateList2);
}
