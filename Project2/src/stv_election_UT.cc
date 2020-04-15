/**
 * @file STV_election_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include "../src/stv_election.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class STVElectionTests : public ::testing::Test {
 protected:
  VotingInfo* votinginfo1;
  VotingInfo* votinginfo2;
  Ballot* ballot1;
  Ballot* ballot2;
  Ballot* ballot3;
  Ballot* ballot4;
  Ballot* ballot5;
  Ballot* ballot6;
  Ballot* ballot7;
  Ballot* ballot8;
  Ballot* ballot9;
  Ballot* ballot10;
  Candidate* candidate1;
  Candidate* candidate2;
  std::list<int> candidateList1, candidateList2, candidateDup;
  int i;
  STVElection* pElection;
  virtual void SetUp() {
    votinginfo1 = new VotingInfo(0, 2);  // STV, 3 candidates
    votinginfo2 = new VotingInfo(1, 2);  // STV, 3 candidates
    candidateList1.push_back(1);
    candidateList2.push_back(2);
    ballot1 = new Ballot(1, candidateList1);
    ballot2 = new Ballot(2, candidateList2);
    ballot3 = new Ballot(3, candidateList1);
    ballot4 = new Ballot(4, candidateList2);
    ballot5 = new Ballot(5, candidateList1);
    ballot6 = new Ballot(6, candidateList2);
    ballot7 = new Ballot(7, candidateList1);
    ballot8 = new Ballot(8, candidateList2);
    ballot9 = new Ballot(9, candidateList1);
    ballot10 = new Ballot(10, candidateList2);
    candidate1 = new STVCandidate(1, "Allison", "Democrat");
    candidate1 = new STVCandidate(2, "Mark", "Independant");
  }
  virtual void TearDown() {
    delete ballot1;
    delete ballot2;
    delete ballot3;
    delete ballot4;
    delete ballot5;
    delete ballot6;
    delete ballot7;
    delete ballot8;
    delete ballot9;
    delete ballot10;
    delete candidate1;
    delete candidate2;
  }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(STVElectionTests, Constructor) {
    EXPECT_NO_THROW(pElection = new STVElection());
    // Add more tests
}

TEST_F(STVElectionTests, RunElection) {
    EXPECT_NO_THROW(pElection->RunElection(votinginfo1));
    EXPECT_NE(candidate1->GetNumBallots(), 1);
    // Add tests
}
