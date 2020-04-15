/**
 * @file STVElectionRecord_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include <string>
#include "../src/ballot.h"
#include "../src/candidate.h"
#include "../src/stv_election_record.h"


bool BallotShuffleOff = false;
/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class STVElectionRecordUT : public ::testing::Test {
 protected:
  STVElectionRecord* stver;
  std::list<Ballot*> nonDistributedBallotList;
  std::list<STVCandidate*> nonElectedCandidateList;
  std::list<STVCandidate*> winnersList;
  std::list<STVCandidate*> losersList;
  std::list<int> candidateList1;
  std::list<int> candidateList2;
  std::list<Ballot*> discardedBallotList;
  std::list<Ballot*> loserBallots;
  bool droopMet, droopNMet;
  STVCandidate* stvcandidate1;
  STVCandidate* lastCandidateOnList;
  STVCandidate* loserSTVCandidate;
  STVCandidate* candidate1;
  STVCandidate* candidate2;
  STVCandidate* winningCandidate;
  Ballot* ballot1;
  Ballot* ballot2;
  int i;
  virtual void SetUp() {
    for (i = 0; i < 5; i++) {
        candidateList1.push_back(i);
    }
    for (i = 0; i < 10; i++) {
        candidateList2.push_back(i);
    }
    stvcandidate1 = new STVCandidate(1, "A", "b");
    candidate1 = new STVCandidate(2, "A", "b");
    candidate2 = new STVCandidate(3, "A", "b");
    loserSTVCandidate = new STVCandidate(4, "A", "b");
    ballot1 = new Ballot(1, candidateList1);
    ballot2 = new Ballot(2, candidateList2);
    nonElectedCandidateList.emplace_back(candidate1);
    nonElectedCandidateList.emplace_back(candidate2);
    nonDistributedBallotList.emplace_back(ballot1);
    nonDistributedBallotList.emplace_back(ballot2);
    stver = new STVElectionRecord(nonElectedCandidateList,
                                  nonDistributedBallotList, 10);
  }
  virtual void TearDown() {
    delete stver;
  }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(STVElectionRecordUT, Constructor) {
    std::list<STVCandidate*> nonElectedCandidateList;
    std::list<Ballot*> nonDistributedBallotList;
    std::list<int> candidateList1;
    std::list<int> candidateList2;
    for (i = 0; i < 5; i++) {
        candidateList1.push_back(i);
    }
    for (i = 0; i < 10; i++) {
        candidateList2.push_back(i);
    }
    candidate1 = new STVCandidate(2, "A", "b");
    candidate2 = new STVCandidate(3, "A", "b");
    ballot1 = new Ballot(1, candidateList1);
    ballot2 = new Ballot(2, candidateList2);
    nonElectedCandidateList.emplace_back(candidate1);
    nonElectedCandidateList.emplace_back(candidate2);
    nonDistributedBallotList.emplace_back(ballot1);
    nonDistributedBallotList.emplace_back(ballot2);
    EXPECT_NO_THROW(stver = new STVElectionRecord(nonElectedCandidateList,
                                  nonDistributedBallotList, 10));
}

TEST_F(STVElectionRecordUT, BreakTies) {
    EXPECT_EQ(stver->BreakTies(candidate1, candidate2), candidate1);
    EXPECT_NE(stver->BreakTies(candidate1, candidate2), candidate2);
}
