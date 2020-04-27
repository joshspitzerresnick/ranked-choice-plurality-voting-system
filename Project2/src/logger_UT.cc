/**
 * @file logger_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include "../src/ballot.h"
#include "../src/candidate.h"
#include "../src/voting_info.h"
#include "../src/ballot_file_processor.h"
#include "../src/logger.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class LoggerTests : public ::testing::Test {
 protected:
  std::string pl_ballot_file_name;
  std::string stv_ballot_file_name;
  VotingInfo* votinginfop;
  VotingInfo* votinginfos;
  BallotFileProcessor* pbfp;
  BallotFileProcessor* sbfp;
  std::list<Candidate*> cand_list;
  std::list<STVCandidate*> new_cand_list;
  std::list<Ballot*> ballot_list;
  std::string testMsg = "Test Message";
  Ballot* ballot1;
  Candidate* candidate1;
  STVCandidate* stv_candidate1;
  std::list<int> candidateList1;
  std::list<std::string> plurality_files;
  std::list<std::string> stv_files;
  int i;
  virtual void SetUp() {
    pl_ballot_file_name = "../testing/plurality_ballots.csv";
    stv_ballot_file_name = "../testing/stv_ballots.csv";
    plurality_files = {"../testing/plurality_20ballots_5candidates.csv",
                       "../testing/plurality_110ballots_5candidates.csv"};
    pbfp = new BallotFileProcessor();
    votinginfop = new VotingInfo(0, 1);
    stv_files = {"../testing/stv_20ballots_5candidates_0pctBadBallots.csv",
                       "../testing/stv_100ballots_5candidates_0pctBadBallots.csv"};
    sbfp = new BallotFileProcessor();
    votinginfos = new VotingInfo(1, 2);
    for (i = 0; i < 5; i++) {
        candidateList1.push_back(i);
    }
    ballot1 = new Ballot(1, candidateList1);
    candidate1 = new Candidate(1, "Allison", "Democrat");
    stv_candidate1 = new STVCandidate(2, "Mark", "Independant");
  }
  virtual void TearDown() {
  }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(LoggerTests, Constructor) {
  EXPECT_NO_THROW(Logger::GetLogger());
}

TEST_F(LoggerTests, LogMsgToFile) {
  Logger::GetLogger()->Log("Test print string messages:");
  EXPECT_NO_THROW(Logger::GetLogger()->Log(testMsg));
  EXPECT_NO_THROW(Logger::GetLogger()->Log("This is a test... 2nd message"));
  EXPECT_NO_THROW(LOGGER->Log("This is a test... 3rd message"));
  Logger::GetLogger()->Log(" ");
}

TEST_F(LoggerTests, LogListToFile) {
  Logger::GetLogger()->Log("Test print a list of integers:");
  EXPECT_NO_THROW(Logger::GetLogger()->Log({2, 4, 6, 8, 10}));
  Logger::GetLogger()->Log(" ");
}

TEST_F(LoggerTests, LogCandidateListToFile) {
  Logger::GetLogger()->Log("Test print a list of plurality candidates:");
  pbfp->ProcessFiles(plurality_files, votinginfop);
  cand_list = votinginfop->GetCandidateList();
  EXPECT_NO_THROW(Logger::GetLogger()->Log(cand_list));
  Logger::GetLogger()->Log(" ");
  Logger::GetLogger()->Log("Test print a list of stv candidates:");
  sbfp->ProcessFiles(stv_files, votinginfos);
  cand_list = votinginfos->GetCandidateList();
  EXPECT_NO_THROW(Logger::GetLogger()->Log(cand_list));
  Logger::GetLogger()->Log(" ");
}

TEST_F(LoggerTests, LogBallotListToFile) {
  Logger::GetLogger()->Log("Test print a list of plurality ballots:");
  pbfp->ProcessFiles(plurality_files, votinginfop);
  ballot_list = votinginfop->GetBallotList();
  EXPECT_NO_THROW(Logger::GetLogger()->Log(ballot_list));
  Logger::GetLogger()->Log(" ");
  Logger::GetLogger()->Log("Test print a list of stv ballots:");
  sbfp->ProcessFiles(stv_files, votinginfos);
  ballot_list = votinginfos->GetBallotList();
  EXPECT_NO_THROW(Logger::GetLogger()->Log(ballot_list));
  Logger::GetLogger()->Log(" ");
}
