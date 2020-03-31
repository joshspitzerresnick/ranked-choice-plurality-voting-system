/**
 * @file candidate_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include "../src/plurality_election_record.cc"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class PluralityElectionRecordTests : public ::testing::Test {

	protected:
		Candidate* candidate1;
		Candidate* candidate2;
		Candidate* candidate3;
		Ballot* ballot1;
		Ballot* ballot2;
		Ballot* ballot3;
        std::list<Candidate*> candidates;
        std::list<Ballot*> ballots;
        //ElectionRecord* election_record;


		virtual void SetUp() {
			candidate1 = new Candidate(1, "Al", "left");
			candidate2 = new Candidate(2, "Beth", "center");
			candidate3 = new Candidate(3, "Carl", "right");
			ballot1 = new Ballot(1, {1});
			ballot2 = new Ballot(2, {1});
			ballot3 = new Ballot(3, {1});
            candidates.push_front(candidate1);
            candidates.push_front(candidate2);
            candidates.push_front(candidate3);
            ballots.push_front(ballot1);
            ballots.push_front(ballot2);
            ballots.push_front(ballot3);
            //election_record = new PluralityElectionRecord(candidates, ballots);
			//election_record->test();


  	}

  	virtual void TearDown() {

			delete candidate1;
			delete candidate2;
			delete candidate3;
			delete ballot1;
			delete ballot2;
			delete ballot3;
  	}

};




/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(PluralityElectionRecordTests, Constructor) {

/*
	std::list<Candidate*> candidate_list = election_record->GetNonElectedCandidateList();
	std::list<Ballot*> ballot_list = election_record->GetNonDistributedBallotList();
	ASSERT_EQ(candidate_list, candidates);
	ASSERT_EQ(ballot_list, ballots);
	*/
	
    // Add more tests
}

TEST_F(PluralityElectionRecordTests, DistributeBallots) {
    // Add tests
	/*
	election_record->DistributeBallots();
	std::list<Ballot*> ballot_list = election_record->GetNonDistributedBallotList();
	ASSERT_EQ(ballot_list, std::list<Ballot*>{});
	*/
}

TEST_F(PluralityElectionRecordTests, SortNonElectedCandidateList) {
    // Add tests
}

TEST_F(PluralityElectionRecordTests, BreakTies) {
	/*
	Candidate* test_candidate = election_record->BreakTies(candidate1, candidate2);
	ASSERT_EQ(true, (candidate1 == test_candidate) || ( candidate2 == test_candidate));
	*/
    // Add tests
}

TEST_F(PluralityElectionRecordTests, MoveFirstNCandidatesFromNonElectedListToWinnersList) {
    // Add tests
}

TEST_F(PluralityElectionRecordTests, MoveFirstNCandidatesFromNonElectedListToLosersList) {
    // Add tests
}

TEST_F(PluralityElectionRecordTests, GetWinnersList) {
    // Add tests
}

TEST_F(PluralityElectionRecordTests, GetLosersList) {
    // Add tests
}

TEST_F(PluralityElectionRecordTests, GetNonElectedCandidateList) {
    // Add tests
}

TEST_F(PluralityElectionRecordTests, GetNonDistributedBallotList) {
    // Add tests
}

