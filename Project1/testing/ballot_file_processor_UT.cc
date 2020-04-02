/**
 * @file ballot_file_processor_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include "../src/ballot_file_processor.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class BallotFileTests : public ::testing::Test {
 protected:
  std::string pl_ballot_file_name;
  std::string stv_ballot_file_name;
  VotingInfo* votinginfop;
  VotingInfo* votinginfos;
  BallotFileProcessor* pbfp;
  BallotFileProcessor* sbfp;
  Candidate *can1, *can2, *can3, *can4, *can5, *can6, *temp;
  std::list<Candidate*> cand_list;
  std::list<Candidate*> new_cand_list;
  std::list<int> cand_ints;
  Ballot* ballot1;
  Ballot* ballot2;
  Ballot* ballot3;
  Ballot* tempballot;
  std::list<Ballot*> ballot_list;
  std::list<Ballot*> new_ballot_list;
  int i;
  virtual void SetUp() {
    for (i=0; i < 6; i++) {
        cand_ints.push_back(i);
    }
    ballot1 = new Ballot(1, std::list<int>{0});
    ballot2 = new Ballot(2, std::list<int>{2});
    ballot3 = new Ballot(3, std::list<int>{5});
    ballot_list.push_back(ballot1);
    ballot_list.push_back(ballot2);
    ballot_list.push_back(ballot3);
    can1 = new Candidate(0, "A", "Ind");
    can2 = new Candidate(1, "B", "Ind");
    can3 = new Candidate(2, "C", "Ind");
    can4 = new Candidate(3, "D", "Ind");
    can5 = new Candidate(4, "E", "Ind");
    can6 = new Candidate(5, "F", "Ind");
    cand_list.push_back(can1);
    cand_list.push_back(can2);
    cand_list.push_back(can3);
    cand_list.push_back(can4);
    cand_list.push_back(can5);
    cand_list.push_back(can6);
    pl_ballot_file_name = "../src/plurality_ballots.csv";
    stv_ballot_file_name = "../src/stv_ballots.csv";
    pbfp = new BallotFileProcessor(pl_ballot_file_name);
    votinginfop = new VotingInfo(0, 1);
    sbfp = new BallotFileProcessor(stv_ballot_file_name);
    votinginfos = new VotingInfo(1, 2);
  }
  virtual void TearDown() {
    delete pbfp;
    delete sbfp;
  }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(BallotFileTests, Constructor) {
    // Check normal construction
    EXPECT_NO_THROW(pbfp = new BallotFileProcessor(pl_ballot_file_name));
    EXPECT_NO_THROW(sbfp = new BallotFileProcessor(stv_ballot_file_name));
}

TEST_F(BallotFileTests, ProcessPluralityBallots) {
    // Process plurality ballots
    pbfp->ProcessFiles(votinginfop);
    // Check that the correct number of candidates were created.
    EXPECT_EQ(votinginfop->GetNumCandidates(), 6);
    // Check that the correct number of ballots were created.
    EXPECT_EQ(votinginfop->GetNumBallots(), 3);
    // Check that the first candidate added has the correct id and name
    new_cand_list = votinginfop->GetCandidateList();
    temp = new_cand_list.front();
    EXPECT_EQ(temp->GetID(), 0);
    EXPECT_EQ(temp->GetName(), "A");
    // Check that the first ballot added has the correct id and candidate list
    new_ballot_list = votinginfop->GetBallotList();
    tempballot = new_ballot_list.front();
    EXPECT_EQ(tempballot->GetID(), 1);
    EXPECT_EQ(tempballot->GetRankedCandidateIDList().front(), 0);
}

TEST_F(BallotFileTests, ProcessSTVBallots) {
    // Process stv ballots
    sbfp->ProcessFiles(votinginfos);
    // Check tha tthe correct number of candidates were created.
    EXPECT_EQ(votinginfos->GetNumCandidates(), 6);
    // Check that the correct number of ballots were created.
    EXPECT_EQ(votinginfos->GetNumBallots(), 4);
    // Check that the first candidate added has the correct id and name
    new_cand_list = votinginfos->GetCandidateList();
    temp = new_cand_list.front();
    EXPECT_EQ(temp->GetID(), 0);
    EXPECT_EQ(temp->GetName(), "A");
    // Check that the first ballot added has the correct id and candidate list
    new_ballot_list = votinginfos->GetBallotList();
    tempballot = new_ballot_list.front();
    EXPECT_EQ(tempballot->GetID(), 1);
    EXPECT_EQ(tempballot->GetRankedCandidateIDList().front(), 0);
}
