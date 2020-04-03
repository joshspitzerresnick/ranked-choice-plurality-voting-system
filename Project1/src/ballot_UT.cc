/**
 * @file ballot_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include "../src/ballot.h"

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
    // Negative ballot id should throw exception.
    EXPECT_ANY_THROW(ballot1 = new Ballot(-1, candidateList1));
    // Duplicate candidate id should throw exception.
    EXPECT_ANY_THROW(ballot1 = new Ballot(1, candidateDup));
    // Common ballot definitions.
    EXPECT_NO_THROW(ballot1 = new Ballot(1, candidateList1));
    EXPECT_NO_THROW(ballot2 = new Ballot(2, candidateList2));
}

TEST_F(BallotTests, GetID) {
    // Check for correct return of ballot ids.
    EXPECT_EQ(ballot1->GetID(), 1);
    EXPECT_EQ(ballot2->GetID(), 2);
}

TEST_F(BallotTests, GetRankedCandidateList) {
    // Check for correct return of candidate id list.
    EXPECT_EQ(ballot1->GetRankedCandidateIDList(), candidateList1);
    EXPECT_EQ(ballot2->GetRankedCandidateIDList(), candidateList2);
}
