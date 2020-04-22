/**
 * @file stv_election_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include "../src/stv_election.h"

bool BallotShuffleOff = true;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class STVElectionTests : public ::testing::Test {
 protected:
  VotingInfo* votinginfo;
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
  STVCandidate* candidate1;
  STVCandidate* candidate2;
  std::list<int> candidateList1, candidateList2, candidateDup;
  int i;
  int* ip;
  STVElection* stvElection;
  virtual void SetUp() {
    votinginfo = new VotingInfo(1, 2);  // STV, 3 candidates
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
    candidate2 = new STVCandidate(2, "Mark", "Independant");
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
  EXPECT_NO_THROW(stvElection = new STVElection(votinginfo));
}

TEST_F(STVElectionTests, RunElection) {
  stvElection = new STVElection(votinginfo);
  EXPECT_NO_THROW(stvElection->RunElection(votinginfo));
}

TEST_F(STVElectionTests, DisplayResults) {
  stvElection = new STVElection(votinginfo);
  EXPECT_NO_THROW(stvElection->DisplayResult(votinginfo));
}
