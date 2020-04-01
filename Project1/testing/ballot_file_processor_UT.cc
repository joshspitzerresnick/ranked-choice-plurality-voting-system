/**
 * @file ballot_file_processor_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include "../src/ballot_file_processor.cc"

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
  Candidate *can1, *can2, *can3, *can4, *can5, *can6;
  std::list<Candidate*> cand_list;
  std::list<int> cand_ints;
  Ballot* ballot1;
  Ballot* ballot2;
  Ballot* ballot3;
  std::list<Ballot*> ballot_list;
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
    can3 = new Candidate(1, "C", "Ind");
    can4 = new Candidate(1, "D", "Ind");
    can5 = new Candidate(1, "E", "Ind");
    can6 = new Candidate(1, "F", "Ind");
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
    EXPECT_NO_THROW(pbfp = new BallotFileProcessor(pl_ballot_file_name));
    EXPECT_NO_THROW(sbfp = new BallotFileProcessor(stv_ballot_file_name));
}

TEST_F(BallotFileTests, ProcessFiles) {
    pbfp->ProcessFiles(votinginfop);
    EXPECT_EQ(votinginfop->GetNumCandidates(), 6);
    EXPECT_EQ(votinginfop->GetNumBallots(), 3);
    EXPECT_EQ(votinginfop->GetCandidateList(), cand_list);
    EXPECT_EQ(votinginfop->GetBallotList(), ballot_list);
    // sbfp->ProcessFiles(votinginfos);
}
