/**
 * @file STVElectionRecord_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
// #include "../src/ballot.cc"
#include "STVElectionRecord.h"
#include "STVElectionRecord.cc"
#include "ElectionRecord.h"
#include "STVCandidate.h"
#include "Ballot.h"
#include "Candidate.h"
// #include "ballot.cc"
// #include "candidate.cc"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class STVElectionRecordUT : public ::testing::Test {
 protected:
  STVElectionRecord* stver;
  std::list<Ballot*> nonDistributedBallotList;
  std::list<Candidate*> nonElectedCandidateList;
  std::list<Candidate*> winnersList;
  std::list<Candidate*> losersList;
  std::list<Ballot*> discardedBallotList, loserBallots;
  bool droopMet, droopNMet;
  STVCandidate* stvcandidate1,lastCandidateOnList, loserSTVCandidate;
  Candidate* candidate1, candidate2, winningCandidate;
  int *i1, *i2, *i;


  virtual void SetUp() {
    stver = new STVElectionRecord();
    stvcandidate1 = new STVCandidate(1,"A","b");
    candidate1= new STVCandidate(2,"A","b");
    candidate2= new STVCandidate(3,"A","b");
    loserSTVCandidate= new STVCandidate(4,"A","b");
    // winningCandidate= new STVCandidate();
    // lastCandidateOnList= new STVCandidate();
    *i1=1; 
    *i2=2;
    nonDistributedBallotList=stver->GetNonDistributedBallotList();
    nonElectedCandidateList=stver->GetNonElectedCandidateList();
    winnersList=stver->GetWinnersList();
    losersList=stver->GetLosersList();
    discardedBallotList=stver->GetDiscardedBallotList();
    // candidatelist=stver->BreakTies(candidatelist);
    droopMet=stver->CheckDroop(1);
    droopNMet=stver->CheckDroop(-1);
    // winningCandidate = stver->BreakTies(candidate1,candidate2);
    i=stver->dummyf(i1,i2);
    lastCandidateOnList=stver->RemoveLastCandidateFromNonElectedCandidateList();

    loserBallots = stver->AddCandidateToLosersList(&loserSTVCandidate);
  }
  virtual void TearDown() {
    delete stver;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
// TEST(STVElectionRecordUniteTest, CanReturnDroopQuota){
//     STVElectionRecord* stver;
//     stver = new STVElectionRecord();
//     ASSERT_EQ(0, stver->GetDroopQuota());
//     ASSERT_EQ(0, stver->GetNonDistributedBallotList().empty());
// }


TEST_F(STVElectionRecordUT, Constructor) {
    // EXPECT_ANY_THROW(ballot1 = new Ballot(-1, candidateList1));
    // EXPECT_ANY_THROW(ballot1 = new Ballot(1, candidateDup));
    EXPECT_NO_THROW(stver = new STVElectionRecord());
    // EXPECT_NO_THROW(ballot2 = new Ballot(2, candidateList2));
}

TEST_F(STVElectionRecordUT, GetDroopQuota) {
    EXPECT_EQ(0, stver->GetDroopQuota());
}

TEST_F(STVElectionRecordUT, GetNonDistributedBallotList) {
    EXPECT_TRUE(nonDistributedBallotList.empty());
}

TEST_F(STVElectionRecordUT, GetNonElectedCandidateList) {
    EXPECT_TRUE(nonElectedCandidateList.empty());
}

TEST_F(STVElectionRecordUT, GetWinnersList) {
    EXPECT_TRUE(winnersList.empty());
}

TEST_F(STVElectionRecordUT, GetLosersList) {
    EXPECT_TRUE(losersList.empty());
}

TEST_F(STVElectionRecordUT, DistributeBallots) {
    EXPECT_NO_THROW(stver->DistributeBallots());
}

TEST_F(STVElectionRecordUT, SortNonElectedCandidateList) {
    EXPECT_NO_THROW(stver->SortNonElectedCandidateList());
}

TEST_F(STVElectionRecordUT, CheckDroop) {
    EXPECT_TRUE(droopNMet);
    EXPECT_FALSE(droopNMet);
}

TEST_F(STVElectionRecordUT, AddCandidateToWinnersList) {
    EXPECT_NO_THROW(stver->AddCandidateToWinnersList(stvcandidate1));
}

TEST_F(STVElectionRecordUT, dummyf) {
    EXPECT_EQ(1,*i);
}

// TEST_F(STVElectionRecordUT, BreakTies) {
//     EXPECT_EQ(candidate1, winningCandidate);
// }

// TEST_F(BallotTests, GetRankedCandidateList) {
//     EXPECT_EQ(ballot1->GetRankedCandidateIDList(), candidateList1);
//     EXPECT_EQ(ballot2->GetRankedCandidateIDList(), candidateList2);
// }